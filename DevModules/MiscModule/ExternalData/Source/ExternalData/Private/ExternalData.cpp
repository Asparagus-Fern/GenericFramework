// Copyright ChenTaiye 2025,. All Rights Reserved.

#include "ExternalData.h"

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
	
	#if PLATFORM_WINDOWS
	static FString ExternalData(TEXT("ExternalData"));
	static FString Extension(TEXT(".json"));

	return FPaths::Combine(FPaths::ProjectConfigDir(), ExternalData, InName + Extension);
	// #elif PLATFORM_ANDROID
	// return FPaths::Combine(FPaths::ProjectConfigDir(), ExternalData, InName + Extension);
	#endif
}

bool UExternalData::LoadData()
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *GetJsonFilePath(GetName())) || JsonString.IsEmpty())
	{
		UE_LOG(LogExternalData, Warning, TEXT("Json data load fail, invalid jons file : %s"), *GetName())
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogExternalData, Warning, TEXT("Json data serializer fail, invalid jons file : %s"), *GetName())
		return false;
	}

	if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), RowStruct.GetScriptStruct(), RowStruct.GetMutableMemory()))
	{
		UE_LOG(LogExternalData, Warning, TEXT("Json data converter fail, invalid jons file : %s"), *GetName())
		return false;
	}

	return true;
}

bool UExternalData::SaveData() const
{
	if (!RowStruct.IsValid())
	{
		return false;
	}

	FString JsonString;
	ensure(FJsonObjectConverter::UStructToJsonObjectString(RowStruct.GetScriptStruct(), RowStruct.GetMemory(), JsonString) || JsonString.IsEmpty());
	return FFileHelper::SaveStringToFile(JsonString, *GetJsonFilePath(GetName()));
}

#undef LOCTEXT_NAMESPACE
