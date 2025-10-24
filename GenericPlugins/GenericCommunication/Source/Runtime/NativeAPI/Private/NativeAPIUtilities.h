// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPITypes.h"

class FJsonValue;

/**
 * 
 */
class FNativeAPIUtilities
{
public:
	
	/**
	 * 检查是否为 NativeAPI 格式的 Json 对象.
	 */
	static bool IsNativeAPIJson(const TSharedPtr<FJsonObject>& Json);
	
	/**
	 * 检查是否为 NativeAPI 格式的函数名称.
	 */
	static bool IsNativeAPIFunctionName(const FName& InName);
	
	/**
	 * 将 Native API Json 转换为 Native API Payload 对象. 
	 * @param InJson Native api 格式 JSON
	 * @param OutPayload Payload, 用于在 UE 内部处理 NativeAPI 的凭据.
	 * @return 如果转换失败将返回 false .
	 */
	static bool ConvertNativeAPIJsonToPayload(const TSharedPtr<FJsonObject>& InJson, FNativeAPIPayload& OutPayload);
	
	// --------------------------------------------------------------------------------------------------------------------------------------
	// See FEditorConfig
	static void ReadStruct(const TSharedPtr<FJsonObject>& JsonObject, const UStruct* Struct, void* Instance, UObject* Owner);
	static void ReadValue(const TSharedPtr<FJsonValue>& JsonValue, const FProperty* Property, void* DataPtr, UObject* Owner);

	static TSharedPtr<FJsonObject> WriteStruct(const UStruct* Struct, const void* Instance, const void* Defaults);
	static TSharedPtr<FJsonObject> WriteUObject(const UClass* Class, const UObject* Instance);
	static TSharedPtr<FJsonValue> WriteArray(const FArrayProperty* ArrayProperty, const void* DataPtr);
	static TSharedPtr<FJsonValue> WriteSet(const FSetProperty* Property, const void* DataPtr);
	static TSharedPtr<FJsonValue> WriteMap(const FMapProperty* Property, const void* DataPtr);
	static TSharedPtr<FJsonValue> WriteValue(const FProperty* Property, const void* DataPtr, const void* Defaults);
	// See FEditorConfig

	static TSharedPtr<FJsonObject> WriteFunction(const UFunction* Function, const void* Defaults);

};