// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTTPType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SendHttpRequestAsyncAction.generated.h"

class UGenericHttpResponse;
class UGenericHttpRequest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestEvent, EHttpRequestStatusBP, ConnectionStatus, UGenericHttpRequest*, Request);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnResponseEvent, EHttpRequestStatusBP, ConnectionStatus, UGenericHttpRequest*, Request, UGenericHttpResponse*, Response, EHttpResponseCode, ResponseCode);

/**
 * 
 */
UCLASS(Abstract)
class GENERICPROTOCOL_API USendHttpRequestAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:
	virtual void OnSuccessInternal(UGenericHttpResponse* Response) { return; }
	virtual void OnErrorInternal(UGenericHttpResponse* Response) { return; }
	virtual void OnTickInternal() { return; }

	void CreateRequest(UGenericHttpRequest* InRequest = nullptr);
	void SendRequest();

	int32 GetBytesSent() const { return BytesSent; }
	int32 GetBytesReceived() const { return BytesReceived; }
	UGenericHttpRequest* GetRequest() { return Request; }

private:
	UFUNCTION()
	void OnRequestProgress(UGenericHttpRequest* InRequest, const int32 InBytesSent, const int32 InBytesReceived);

	UFUNCTION()
	void OnRequestComplete(UGenericHttpRequest* InRequest, UGenericHttpResponse* InResponse, const bool bConnectedSuccessfully);

private:
	UPROPERTY()
	UGenericHttpRequest* Request = nullptr;

	int32 BytesSent = 0;
	int32 BytesReceived = 0;
};


/**
 * 
 */
UCLASS(MinimalAPI)
class USendHttpRequestAsyncAction : public USendHttpRequestAsyncActionBase
{
	GENERATED_BODY()

public:
	/* 
	* 向指定的URL发送Http请求。
	* @param ServerUrl 连接的服务器。
	* @param UrlParameters 要添加到URL中的可选未配置的参数。
	* @param Verb 我们要用于此请求Verb
	* @param MimeType MIME 类型
	* @param Content 此请求的内容。
	* @param Headers 此请求的标头。
	**/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="HTTP")
	static USendHttpRequestAsyncAction* SendHttpRequest(UGenericHttpRequest* InRequest);

public:
	/* 当此请求勾选并已下载或上载部分数据时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnRequestEvent OnTick;

	/* 从服务器发送成功响应时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnSuccess;

	/* 发生错误时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnError;

protected:
	virtual void OnTickInternal() override;
	virtual void OnSuccessInternal(UGenericHttpResponse* Response) override;
	virtual void OnErrorInternal(UGenericHttpResponse* Response) override;
};


/**
 * 
 */
UCLASS(MinimalAPI)
class USendHttpStringRequestAsyncAction : public USendHttpRequestAsyncActionBase
{
	GENERATED_BODY()

public:
	/* 
	* 向指定的URL发送Http请求。
	* @param ServerUrl 连接的服务器。
	* @param UrlParameters 要添加到URL中的可选未配置的参数。
	* @param Verb 我们要用于此请求Verb
	* @param MimeType MIME 类型
	* @param Content 此请求的内容。
	* @param Headers 此请求的标头。
	**/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "Headers, UrlParameters"), Category ="HTTP")
	static USendHttpStringRequestAsyncAction* SendHttpStringRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const FString& Content, const TMap<FString, FString>& Headers);

public:
	/* 当此请求勾选并已下载或上载部分数据时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnRequestEvent OnTick;

	/* 从服务器发送成功响应时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnSuccess;

	/* 发生错误时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnError;

protected:
	virtual void OnTickInternal() override;
	virtual void OnSuccessInternal(UGenericHttpResponse* Response) override;
	virtual void OnErrorInternal(UGenericHttpResponse* Response) override;
};


/**
 * 
 */
UCLASS(MinimalAPI)
class USendHttpBinaryRequestAsyncAction : public USendHttpRequestAsyncActionBase
{
	GENERATED_BODY()

public:
	/* 
	* 向指定的URL发送Http请求。
	* @param ServerUrl 连接的服务器。
	* @param UrlParameters 要添加到URL中的可选未配置的参数。
	* @param Verb 我们要用于此请求Verb
	* @param MimeType MIME 类型
	* @param Content 此请求的内容。
	* @param Headers 此请求的标头。
	**/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "Headers, UrlParameters"), Category ="HTTP")
	static USendHttpBinaryRequestAsyncAction* SendHttpBinaryRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const TArray<uint8>& Content, const TMap<FString, FString>& Headers);

public:
	/* 当此请求勾选并已下载或上载部分数据时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnRequestEvent OnTick;

	/* 从服务器发送成功响应时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnSuccess;

	/* 发生错误时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnResponseEvent OnError;

protected:
	virtual void OnTickInternal() override;
	virtual void OnSuccessInternal(UGenericHttpResponse* Response) override;
	virtual void OnErrorInternal(UGenericHttpResponse* Response) override;
};
