// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTTPType.h"
#include "Obect/GenericObject.h"
#include "Interfaces/IHttpRequest.h"
#include "GenericHttpRequest.generated.h"

class UGenericHttpResponse;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestComplete, UGenericHttpRequest*, Request, UGenericHttpResponse*, Response, bool, bConnectedSuccessfully);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestProgress, UGenericHttpRequest*, Request, int32, BytesSent, int32, BytesReceived);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestHeaderReceived, UGenericHttpRequest*, Request, FString, HeaderName, FString, NewHeaderValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestWillRetry, UGenericHttpRequest*, Request, UGenericHttpResponse*, Response, float, SecondsToRetry);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericHttpRequest : public UGenericObject
{
	GENERATED_BODY()

public:
	UGenericHttpRequest(const FObjectInitializer& ObjectInitializer);

	/* 创建 HTTP Request */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	static GENERICPROTOCOL_API UGenericHttpRequest* CreateHTTPRequest();

public:
	/* 获取二进制 content */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API void GetContent(TArray<uint8>& OutContent) const;

	/* 设置Content为binary data */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetContent(const TArray<uint8>& InContent);

	/* 获取string content */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetContentAsString() const;

	/* 设置content为string */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetContentAsString(const FString& InContent);

	/* 将请求的content设置为从文件流式传输 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetContentAsStreamedFile(const FString& InFileName, bool& bFileValid);

	/* 返回标头中的内容长度（如果可用或为零） */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API int32 GetContentLength() const;

	/* 若可用返回content type */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetContentType() const;

	/* 返回服务器完全响应花费时间 */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API float GetElapsedTime() const;

	/* 返回 header的key */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetHeader(const FString& Key) const;

	/* 设置Header */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetHeader(const FString& Key, const FString& Value);

	/* 返回所有标头Headers */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API TMap<FString, FString> GetHeaders() const;

	/* 设置Headers */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetHeaders(const TMap<FString, FString>& Headers);

	/* 在现有末尾添加Header */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void AppendToHeader(const FString& Key, const FString& Value);

	/* 返回状态 */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API EHttpRequestStatusBP GetStatus() const;

	/* 返回URL */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetURL() const;

	/* 设置URL */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetURL(FString InURL);

	/* 设置URL */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetURLWithParameter(FString InURL, const TMap<FString, FString>& InParameters);

	/* 返回URL参数 */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetURLParameter(const FString& InParameterName) const;

	/* 获取verb */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API FString GetVerb() const;

	/* 设置Verb */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetVerb(FString InVerb);

	/* 获取verb */
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API EHttpVerb GetVerbAsEnum() const;

	/* 设置Verb */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetVerbAsEnum(const EHttpVerb InVerb);

	/* 设置MineType */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetMimeType(const EHttpMimeType InMimeType);

	/* 通过string方式设置MineType */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetMimeTypeAsString(const FString& InMimeType);

	/* Timeout */
public:
	UFUNCTION(BlueprintPure, Category = "HTTP")
	GENERICPROTOCOL_API float GetTimeout() const;

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetTimeout(float InTimeoutSecs);

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void SetActivityTimeout(float InTimeoutSecs);

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void ClearTimeout();

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void ResetTimeoutStatus();

public:
	/* 获取请求进度 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API bool ProcessRequest();

	/* 取消Request */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	GENERICPROTOCOL_API void CancelRequest();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "HTTP")
	FOnRequestComplete OnRequestComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "HTTP")
	FOnRequestProgress OnRequestProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "HTTP")
	FOnRequestHeaderReceived OnRequestHeaderReceived;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "HTTP")
	FOnRequestWillRetry OnRequestWillRetry;

protected:
	virtual void OnHeaderReceivedInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, const FString& HeaderName, const FString& HeaderValue);
	virtual void OnRequestProgressInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, uint64 BytesSent, uint64 BytesReceived);
	virtual void OnRequestCompleteInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, bool bConnectedSuccessfully);
	virtual void OnRequestWillRetryInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, float SecondsToRetry);

	virtual UGenericHttpResponse* CreateResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>& RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe>& RawResponse);

private:
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request;
};
