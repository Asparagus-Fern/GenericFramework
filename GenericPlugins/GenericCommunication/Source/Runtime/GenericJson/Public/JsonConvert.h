// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "JsonConvert.generated.h"

/**
 * 
 */
struct FIVTrimmedKeyMap
{
	FString LongKey;
	TMap<FString, TSharedPtr<FIVTrimmedKeyMap>> SubMap;

	FString ToString();
};

class GENERICJSON_API FJsonConvert
{
public:
	static FString ToJsonString(const TSharedPtr<FJsonObject>& JsonObject);
	static FString ToJsonString(const TSharedPtr<FJsonValue>& JsonValue);
	static FString ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray);

	static TSharedPtr<FJsonObject> ConstructJsonObject();
	static TSharedPtr<FJsonObject> ConstructJsonObject(const FString& JsonString);

	static bool StructToJsonObject(const UStruct* Struct, const void* StructPtr, const TSharedRef<FJsonObject>& OutJsonObject);
	static bool JsonObjectToStruct(const TSharedPtr<FJsonObject>& JsonObject, const UStruct* Struct, void* StructPtr);

	static bool StructToJsonFile(const FString& FilePath, const UStruct* Struct, const void* StructPtr);
	static bool JsonFileToStruct(const FString& FilePath, const UStruct* Struct, void* StructPtr);

	static TSharedPtr<FJsonValue> ToJsonValue(const TSharedPtr<FJsonObject>& JsonObject);
	static TSharedPtr<FJsonValue> ToJsonValue(const FString& StringValue);
	static TSharedPtr<FJsonValue> ToJsonValue(double NumberValue);
	static TSharedPtr<FJsonValue> ToJsonValue(bool BoolValue);
	static TSharedPtr<FJsonValue> ToJsonValue(const TArray<uint8>& BinaryValue);
	static TSharedPtr<FJsonValue> ToJsonValue(const TArray<TSharedPtr<FJsonValue>>& ArrayValue);

	static TSharedPtr<FJsonValue> JsonStringToJsonValue(const FString& JsonString);
	static TArray<TSharedPtr<FJsonValue>> JsonStringToJsonArray(const FString& JsonString);

private:
	static void TrimValueKeyNames(const TSharedPtr<FJsonValue>& JsonValue);
	static bool TrimKey(const FString& InLongKey, FString& OutTrimmedKey);
	static void SetTrimmedKeyMapForStruct(const TSharedPtr<FIVTrimmedKeyMap>& InMap, const UStruct* Struct);
	static void SetTrimmedKeyMapForProp(TSharedPtr<FIVTrimmedKeyMap>& InMap, FProperty* ArrayInnerProp);
	static void ReplaceJsonValueNamesWithMap(const TSharedPtr<FJsonValue>& InValue, const TSharedPtr<FIVTrimmedKeyMap>& KeyMap);
};
