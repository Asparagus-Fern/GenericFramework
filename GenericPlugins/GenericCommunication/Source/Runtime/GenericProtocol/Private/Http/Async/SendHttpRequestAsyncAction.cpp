// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/Async/SendHttpRequestAsyncAction.h"

#include "Http/GenericHttpRequest.h"
#include "Http/GenericHttpResponse.h"

/* ==================== USendHttpRequestAsyncActionBase ==================== */

void USendHttpRequestAsyncActionBase::CreateRequest(UGenericHttpRequest* InRequest)
{
	if (IsValid(InRequest))
	{
		Request = InRequest;
		Request->OnRequestProgress.RemoveAll(this);
		Request->OnRequestComplete.RemoveAll(this);
	}
	else
	{
		Request = NewObject<UGenericHttpRequest>();
	}

	Request->OnRequestProgress.AddDynamic(this, &USendHttpRequestAsyncActionBase::OnRequestProgress);
	Request->OnRequestComplete.AddDynamic(this, &USendHttpRequestAsyncActionBase::OnRequestComplete);
}

void USendHttpRequestAsyncActionBase::SendRequest()
{
	if (!Request->ProcessRequest())
	{
		OnErrorInternal(nullptr);
	}
}

void USendHttpRequestAsyncActionBase::OnRequestProgress(UGenericHttpRequest* InRequest, const int32 InBytesSent, const int32 InBytesReceived)
{
	BytesSent = InBytesSent;
	BytesReceived = InBytesReceived;

	OnTickInternal();
}

void USendHttpRequestAsyncActionBase::OnRequestComplete(UGenericHttpRequest* InRequest, UGenericHttpResponse* InResponse, const bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		OnSuccessInternal(InResponse);
	}
	else
	{
		OnErrorInternal(InResponse);
	}

	SetReadyToDestroy();
}

/* ==================== USendHttpRequestAsyncAction ==================== */

USendHttpRequestAsyncAction* USendHttpRequestAsyncAction::SendHttpRequest(UGenericHttpRequest* InRequest)
{
	USendHttpRequestAsyncAction* Action = NewObject<USendHttpRequestAsyncAction>();
	Action->CreateRequest(InRequest);
	Action->SendRequest();

	return Action;
}

void USendHttpRequestAsyncAction::OnTickInternal()
{
	Super::OnTickInternal();
	OnTick.Broadcast(GetRequest()->GetStatus(), GetRequest());
}

void USendHttpRequestAsyncAction::OnSuccessInternal(UGenericHttpResponse* Response)
{
	Super::OnSuccessInternal(Response);
	OnSuccess.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}

void USendHttpRequestAsyncAction::OnErrorInternal(UGenericHttpResponse* Response)
{
	Super::OnErrorInternal(Response);
	OnError.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}

/* ==================== USendHttpStringRequestAsyncAction ==================== */

USendHttpStringRequestAsyncAction* USendHttpStringRequestAsyncAction::SendHttpStringRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const FString& Content, const TMap<FString, FString>& Headers)
{
	USendHttpStringRequestAsyncAction* Action = NewObject<USendHttpStringRequestAsyncAction>();
	Action->CreateRequest();

	UGenericHttpRequest* Request = Action->GetRequest();
	Request->SetURLWithParameter(ServerUrl, UrlParameters);
	Request->SetMimeType(MimeType);
	Request->SetVerbAsEnum(Verb);
	Request->SetContentAsString(Content);
	Request->SetHeaders(Headers);

	Action->SendRequest();

	return Action;
}

void USendHttpStringRequestAsyncAction::OnTickInternal()
{
	Super::OnTickInternal();
	OnTick.Broadcast(GetRequest()->GetStatus(), GetRequest());
}

void USendHttpStringRequestAsyncAction::OnSuccessInternal(UGenericHttpResponse* Response)
{
	Super::OnSuccessInternal(Response);
	OnSuccess.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}

void USendHttpStringRequestAsyncAction::OnErrorInternal(UGenericHttpResponse* Response)
{
	Super::OnErrorInternal(Response);
	OnError.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}

/* ==================== USendHttpBinaryRequestAsyncAction ==================== */

USendHttpBinaryRequestAsyncAction* USendHttpBinaryRequestAsyncAction::SendHttpBinaryRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const TArray<uint8>& Content, const TMap<FString, FString>& Headers)
{
	USendHttpBinaryRequestAsyncAction* Action = NewObject<USendHttpBinaryRequestAsyncAction>();
	Action->CreateRequest();

	UGenericHttpRequest* Request = Action->GetRequest();
	Request->SetURLWithParameter(ServerUrl, UrlParameters);
	Request->SetMimeType(MimeType);
	Request->SetVerbAsEnum(Verb);
	Request->SetContent(Content);
	Request->SetHeaders(Headers);

	Action->SendRequest();

	return Action;
}

void USendHttpBinaryRequestAsyncAction::OnTickInternal()
{
	Super::OnTickInternal();
	OnTick.Broadcast(GetRequest()->GetStatus(), GetRequest());
}

void USendHttpBinaryRequestAsyncAction::OnSuccessInternal(UGenericHttpResponse* Response)
{
	Super::OnSuccessInternal(Response);
	OnSuccess.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}

void USendHttpBinaryRequestAsyncAction::OnErrorInternal(UGenericHttpResponse* Response)
{
	Super::OnErrorInternal(Response);
	OnError.Broadcast(GetRequest()->GetStatus(), GetRequest(), Response, ConvertToResponseCodeEnum(Response->GetResponseCode()));
}
