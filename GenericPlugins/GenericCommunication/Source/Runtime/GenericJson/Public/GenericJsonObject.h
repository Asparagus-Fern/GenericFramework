// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "GenericJsonObject.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericJsonObject : public UGenericObject
{
	GENERATED_UCLASS_BODY()

public:
	/* 创建新的 Json object*/
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static GENERICJSON_API UGenericJsonObject* ConstructJsonObject(UObject* WorldContextObject);

	/* 重置所有数据 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	GENERICJSON_API void Reset();

public:
	/* 将Json序列化为字符串 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	GENERICJSON_API bool EncodeJson(FString& OutJsonString);

	/* 从字符串构造 Json 对象 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	GENERICJSON_API bool DecodeJson(const FString& InJsonString);

public:
	GENERICJSON_API TSharedPtr<FJsonObject>& GetJsonObject();
	GENERICJSON_API void SetJsonObject(const TSharedPtr<FJsonObject>& InJsonObject);

	GENERICJSON_API FString GetJsonString();
	GENERICJSON_API void SetJsonString(FString InJsonString);

private:
	TSharedPtr<FJsonObject> JsonObject;
	FString JsonString;
};
