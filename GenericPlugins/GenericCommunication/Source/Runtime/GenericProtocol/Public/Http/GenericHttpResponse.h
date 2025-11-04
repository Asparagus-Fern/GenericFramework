// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Obect/GenericObject.h"
#include "GenericHttpResponse.generated.h"

class UGenericJsonObject;
class IHttpResponse;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericHttpResponse : public UGenericObject
{
	GENERATED_BODY()

private:
	friend class UGenericHttpRequest;

	void InitInternal(TWeakObjectPtr<UGenericHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse);

public:
	/* 获取全部的Headers */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API TMap<FString, FString> GetHeaders() const;

	/* 获取 request的 binary data */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API void GetContent(TArray<uint8>& OutContent) const;

	/* 获取 request的 string data */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetContentAsString() const;

	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API UGenericJsonObject* GetContentAsJson();

	/* 返回标头中的内容长度（如果可用或为零） */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API int32 GetContentLength() const;

	/* 若可用返回content type */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetContentType() const;

	/* 返回 header的key */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetHeader(const FString& Key) const;

	/* 返回状态 */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API int32 GetResponseCode() const;

	/* 获取URL. */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetURL() const;

	/* 获取URL参数. */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetURLParameter(const FString& ParameterName) const;

	/* 返回服务器完全响应请求所花费的时间. */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API float GetElapsedTime() const;

public:
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API UGenericHttpRequest* GetRequest() const;

private:
	TWeakObjectPtr<UGenericHttpRequest> Request = nullptr;
	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericJsonObject> JsonObject = nullptr;
};
