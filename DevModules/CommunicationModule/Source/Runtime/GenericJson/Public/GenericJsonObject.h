// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "GenericJsonObject.generated.h"

/**
 * 
 */
UCLASS()
class GENERICJSON_API UGenericJsonObject : public UGenericObject
{
	GENERATED_UCLASS_BODY()

public:
	/* 创建新的 Json object*/
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UGenericJsonObject* ConstructJsonObject(UObject* WorldContextObject);

	/* 重置所有数据 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void Reset();

public:
	/* 将Json序列化为字符串 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool EncodeJson(FString& OutJsonString);

	/* 从字符串构造 Json 对象 */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool DecodeJson(const FString& InJsonString);

public:
	TSharedPtr<FJsonObject>& GetJsonObject();
	void SetJsonObject(const TSharedPtr<FJsonObject>& InJsonObject);

	FString GetJsonString();
	void SetJsonString(FString InJsonString);

private:
	TSharedPtr<FJsonObject> JsonObject;
	FString JsonString;
};
