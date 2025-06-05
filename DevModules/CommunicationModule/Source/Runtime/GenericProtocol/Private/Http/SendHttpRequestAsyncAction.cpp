// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/SendHttpRequestAsyncAction.h"

#include "Http/HTTPRequest.h"

USendHttpRequestAsyncAction::USendHttpRequestAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Request = NewObject<UHTTPRequest>();
	Request->OnRequestProgress.AddDynamic(this, &USendHttpRequestAsyncAction::OnRequestProgress);
	Request->OnRequestComplete.AddDynamic(this, &USendHttpRequestAsyncAction::OnRequestComplete);
}

void USendHttpRequestAsyncAction::OnRequestProgress(UHTTPRequest* InRequest, const int32 InBytesSent, const int32 InBytesReceived)
{
	BytesSent = InBytesSent;
	BytesReceived = InBytesReceived;

	OnTickInternal();
}

void USendHttpRequestAsyncAction::OnRequestComplete(UHTTPRequest* InRequest, UHTTPResponse* InResponse, const bool bConnectedSuccessfully)
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

void USendHttpRequestAsyncAction::SendRequest()
{
	if (!Request->ProcessRequest())
	{
		OnErrorInternal(nullptr);
	}
}

USendHttpStringRequestAsyncAction* USendHttpStringRequestAsyncAction::SendHttpRequest(const FString& ServerUrl, const TMap<FString, FString>& UrlParameters, const EHttpVerb Verb, const EHttpMimeType MimeType, const FString& Content, const TMap<FString, FString>& Headers)
{
	USendHttpStringRequestAsyncAction* Action = NewObject<USendHttpStringRequestAsyncAction>();

	UHTTPRequest* Request = Action->GetRequest();

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
}

void USendHttpStringRequestAsyncAction::OnErrorInternal(UHTTPResponse* Response)
{
	Super::OnErrorInternal(Response);
}

void USendHttpStringRequestAsyncAction::OnSuccessInternal(UHTTPResponse* Response)
{
	Super::OnSuccessInternal(Response);
}
