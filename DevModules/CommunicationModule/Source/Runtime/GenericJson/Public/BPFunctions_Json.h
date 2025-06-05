// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "JsonConvert.h"
#include "Generic/GenericType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Json.generated.h"

class UJsonObject;

/**
 * 
 */
UCLASS()
class GENERICJSON_API UBPFunctions_Json : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Gets the value of the specified field. */
	UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="Json", meta = (CustomStructureParam = "OutValue", AutoCreateRefTerm = "OutValue"))
	static bool GetJsonField(UJsonObject* JsonObject, const FString& FieldName, int32& OutValue);
	DECLARE_FUNCTION(execGetJsonField);

	/* Adds (new) or sets (existing) the value of the specified field. */
	UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="Json", meta = (CustomStructureParam = "Value", AutoCreateRefTerm = "Value"))
	static void SetJsonField(EGenericResult& Result, UJsonObject* JsonObject, const FString& FieldName, const int32& Value);
	DECLARE_FUNCTION(execSetJsonField);

public:
	/* 将结构体保存为 json 文本 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="Json", meta = (CustomStructureParam = "Value", ExpandEnumAsExecs = "Result"))
	static void SaveStructToJsonFile(EGenericResult& Result, const FString& FilePath, const int32& Value);
	DECLARE_FUNCTION(execSaveStructToJsonFile);

	/* 将 json 文本转化为结构体 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="Json", meta = (CustomStructureParam = "Value", ExpandEnumAsExecs = "Result"))
	static void LoadJsonFileToStruct(EGenericResult& Result, const FString& FilePath, int32& Value);
	DECLARE_FUNCTION(execLoadJsonFileToStruct);

private:
	static bool JsonFieldToProperty(const FString& FieldName, UJsonObject* SourceObject, FProperty* TargetProperty, void* TargetValuePtr);
	static bool PropertyToJsonField(const FString& FieldName, FProperty* SourceProperty, const void* SourceValuePtr, UJsonObject*& TargetObject);
};
