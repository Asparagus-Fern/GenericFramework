// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTTPType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SendHttpRequestAsyncAction.generated.h"

class UHTTPResponse;
class UHTTPRequest;

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnRequestEvent, const int32, ResponseCode, const FHttpHeaders&, Headers, const FString&, ContentType, const FString&, Content, UIVJsonObject*, ResponseJson, const float, TimeElapsed, const EHttpBPRequestStatus, ConnectionStatus);

/**
 * 
 */
UCLASS(Abstract)
class GENERICPROTOCOL_API USendHttpRequestAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	USendHttpRequestAsyncAction(const FObjectInitializer& ObjectInitializer);

private:
	UFUNCTION()
	void OnRequestProgress(UHTTPRequest* InRequest, const int32 InBytesSent, const int32 InBytesReceived);

	UFUNCTION()
	void OnRequestComplete(UHTTPRequest* InRequest, UHTTPResponse* InResponse, const bool bConnectedSuccessfully);

protected:
	virtual void OnTickInternal() { return; }
	virtual void OnSuccessInternal(UHTTPResponse* Response) { return; }
	virtual void OnErrorInternal(UHTTPResponse* Response) { return; }

	int32 GetBytesSent() const { return BytesSent; }
	int32 GetBytesReceived() const { return BytesReceived; }
	UHTTPRequest* GetRequest() { return Request; }

	/*发送请求并处理失败的启动*/
	void SendRequest();

private:
	UPROPERTY()
	UHTTPRequest* Request;

	int32 BytesSent;
	int32 BytesReceived;
};


/**
 * 
 */
UCLASS(MinimalAPI)
class USendHttpStringRequestAsyncAction : public USendHttpRequestAsyncAction
{
	GENERATED_BODY()

public:
	/** 
	* 向指定的URL发送Http请求。
	* @param ServerUrl 连接的服务器。
	* @param UrlParameters 要添加到URL中的可选未配置的参数。
	* @param Verb 我们要用于此请求Verb
	* @param MimeType MIME 类型
	* @param Content 此请求的内容。
	* @param Headers 此请求的标头。
	**/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "Headers, UrlParameters"), DisplayName="Send HTTP Request", Category =IVHTTP)
	static USendHttpStringRequestAsyncAction* SendHttpRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const FString& Content, const TMap<FString, FString>& Headers);

protected:
	virtual void OnTickInternal() override;
	virtual void OnErrorInternal(UHTTPResponse* Response) override;
	virtual void OnSuccessInternal(UHTTPResponse* Response) override;
};
