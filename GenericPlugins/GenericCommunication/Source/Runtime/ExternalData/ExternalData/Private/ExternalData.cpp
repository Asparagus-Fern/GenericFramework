// Copyright ChenTaiye 2025,. All Rights Reserved.

#include "ExternalData.h"

#include "JsonConvert.h"
#include "BPFunctions/BPFunctions_File.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Misc/DataValidation.h"
#include "Misc/Paths.h"
#include "UObject/ObjectSaveContext.h"

#if PLATFORM_ANDROID
#include "BPFunctions/BPFunctions_Android.h"
#endif

#define LOCTEXT_NAMESPACE "FExternalDataModule"

DECLARE_LOG_CATEGORY_CLASS(LogExternalData, Log, All);

UExternalData::UExternalData()
{
}

void UExternalData::PostLoad()
{
	Super::PostLoad();

	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	this->LoadData();
}

#if WITH_EDITOR
void UExternalData::PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext)
{
	Super::PostSaveRoot(ObjectSaveContext);

	if (!SaveData())
	{
		UE_LOG(LogExternalData, Warning, TEXT("%s : Can not save data!"), ANSI_TO_TCHAR(__FUNCTION__))
	}
}
#endif

#if WITH_EDITOR
EDataValidationResult UExternalData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

	if (!RowStruct.IsValid())
	{
		Result = EDataValidationResult::Invalid;
		Context.AddError(LOCTEXT("ExternalData_RowStructNull", "Row Struct can not empty."));
	}

	return Result;
}
#endif

FString UExternalData::GetJsonFilePath()
{
	static FString ExternalData(TEXT("ExternalData"));
	static FString Extension(TEXT(".json"));

#if PLATFORM_WINDOWS
	return FPaths::Combine(FPaths::ProjectConfigDir(), ExternalData, GetName() + Extension);
#elif PLATFORM_ANDROID
	FString AndroidExternalStorageJsonFilePath = FPaths::Combine(UBPFunctions_Android::GetAndroidConfigDir(true), ExternalData, GetName() + Extension);
	if (UBPFunctions_File::ExistFile(AndroidExternalStorageJsonFilePath))
	{
		return AndroidExternalStorageJsonFilePath;
	}
	return FPaths::Combine(UBPFunctions_Android::GetAndroidConfigDir(false), ExternalData, GetName() + Extension);
#endif
}

bool UExternalData::LoadData()
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	bool bResult = FJsonConvert::JsonFileToStruct(GetJsonFilePath(), RowStruct.GetScriptStruct(), RowStruct.GetMutableMemory());
	return bResult;
}

bool UExternalData::SaveData()
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	bool bResult = FJsonConvert::StructToJsonFile(GetJsonFilePath(), RowStruct.GetScriptStruct(), RowStruct.GetMemory());
	return bResult;
}

#undef LOCTEXT_NAMESPACE
