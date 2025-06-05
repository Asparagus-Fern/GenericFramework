// Copyright ChenTaiye 2025,. All Rights Reserved.

#include "ExternalData.h"

#include "JsonConvert.h"
#include "JsonConvert.h"
#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Misc/DataValidation.h"
#include "Misc/Paths.h"
#include "UObject/ObjectSaveContext.h"

#define LOCTEXT_NAMESPACE "ExternalData"

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

FString UExternalData::GetJsonFilePath(const FString& InName)
{
	static FString ExternalData(TEXT("ExternalData"));
	static FString Extension(TEXT(".json"));

#if PLATFORM_WINDOWS

	return FPaths::Combine(FPaths::ProjectConfigDir(), ExternalData, InName + Extension);

#elif PLATFORM_ANDROID
	
	static FString AndroidBasePath(TEXT("/sdcard"));
	static FString AndroidConfigPath(TEXT("/Config"));
	
	return FPaths::Combine(AndroidBasePath, TEXT("/"), FApp::GetProjectName(), AndroidConfigPath, ExternalData, InName + Extension);
	
#endif
}

bool UExternalData::LoadData()
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	return FJsonConvert::JsonFileToStruct(GetJsonFilePath(GetName()),RowStruct.GetScriptStruct(), RowStruct.GetMutableMemory());
}

bool UExternalData::SaveData() const
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	return FJsonConvert::StructToJsonFile(GetJsonFilePath(GetName()), RowStruct.GetScriptStruct(), RowStruct.GetMemory());
}

#undef LOCTEXT_NAMESPACE
