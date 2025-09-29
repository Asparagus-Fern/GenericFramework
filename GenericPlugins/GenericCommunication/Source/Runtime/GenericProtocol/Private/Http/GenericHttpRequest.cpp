// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/GenericHttpRequest.h"

#include "HttpModule.h"
#include "Http/BPFunctions_HTTP.h"
#include "Http/GenericHttpResponse.h"

UGenericHttpRequest::UGenericHttpRequest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Request = FHttpModule::Get().CreateRequest();
	if (Request.IsValid())
	{
		Request->OnHeaderReceived().BindUObject(this, &UGenericHttpRequest::OnHeaderReceivedInternal);
		Request->OnRequestProgress64().BindUObject(this, &UGenericHttpRequest::OnRequestProgressInternal);
		Request->OnProcessRequestComplete().BindUObject(this, &UGenericHttpRequest::OnRequestCompleteInternal);
		Request->OnRequestWillRetry().BindUObject(this, &UGenericHttpRequest::OnRequestWillRetryInternal);
	}
}

UGenericHttpRequest* UGenericHttpRequest::CreateHTTPRequest()
{
	return NewObject<UGenericHttpRequest>();
}

void UGenericHttpRequest::GetContent(TArray<uint8>& OutContent) const
{
	OutContent = Request->GetContent();
}

void UGenericHttpRequest::SetContent(const TArray<uint8>& InContent)
{
	Request->SetContent(InContent);
}

FString UGenericHttpRequest::GetContentAsString() const
{
	const TArray<uint8>& Content = Request->GetContent();
	return BytesToString(Content.GetData(), Content.Num());
}

void UGenericHttpRequest::SetContentAsString(const FString& InContent)
{
	Request->SetContentAsString(InContent);
}

void UGenericHttpRequest::SetContentAsStreamedFile(const FString& InFileName, bool& bFileValid)
{
	bFileValid = Request->SetContentAsStreamedFile(InFileName);
}

int32 UGenericHttpRequest::GetContentLength() const
{
	return Request->GetContentLength();
}

FString UGenericHttpRequest::GetContentType() const
{
	return Request->GetContentType();
}

float UGenericHttpRequest::GetElapsedTime() const
{
	return Request->GetContentLength();
}

FString UGenericHttpRequest::GetHeader(const FString& Key) const
{
	return Request->GetContentType();
}

void UGenericHttpRequest::SetHeader(const FString& Key, const FString& Value)
{
	Request->SetHeader(Key, Value);
}

TMap<FString, FString> UGenericHttpRequest::GetHeaders() const
{
	TArray<FString> Headers = Request->GetAllHeaders();

	TMap<FString, FString> OutHeaders;

	FString* Key = nullptr;
	FString* Value = nullptr;

	const FString Separator = TEXT(": ");

	for (FString& Header : Headers)
	{
		if (Header.Split(Separator, Key, Value, ESearchCase::CaseSensitive))
		{
			OutHeaders.Emplace(*Key, *Value);
		}
	}

	return OutHeaders;
}

void UGenericHttpRequest::SetHeaders(const TMap<FString, FString>& Headers)
{
	for (const auto& Header : Headers)
	{
		Request->SetHeader(Header.Key, Header.Value);
	}
}

void UGenericHttpRequest::AppendToHeader(const FString& Key, const FString& Value)
{
	Request->AppendToHeader(Key, Value);
}

EHttpRequestStatusBP UGenericHttpRequest::GetStatus() const
{
	return ConvertToHttpRequestStatusBP(Request->GetStatus());
}

FString UGenericHttpRequest::GetURL() const
{
	return Request->GetURL();
}

void UGenericHttpRequest::SetURL(FString InURL)
{
	Request->SetURL(InURL);
}

void UGenericHttpRequest::SetURLWithParameter(FString InURL, const TMap<FString, FString>& InParameters)
{
	SetURL(UBPFunctions_HTTP::AddParametersToUrl(InURL, InParameters));
}

FString UGenericHttpRequest::GetURLParameter(const FString& InParameterName) const
{
	return Request->GetURLParameter(InParameterName);
}

FString UGenericHttpRequest::GetVerb() const
{
	return Request->GetVerb();
}

void UGenericHttpRequest::SetVerb(FString InVerb)
{
	Request->SetVerb(InVerb);
}

EHttpVerb UGenericHttpRequest::GetVerbAsEnum() const
{
	return ConvertToHttpVerbEnum(Request->GetVerb());
}

void UGenericHttpRequest::SetVerbAsEnum(const EHttpVerb InVerb)
{
	Request->SetVerb(ConvertToHttpVerbString(InVerb));
}

void UGenericHttpRequest::SetMimeType(const EHttpMimeType InMimeType)
{
	Request->AppendToHeader(TEXT("Content-Type"), CreateHttpMimeType(InMimeType));
}

void UGenericHttpRequest::SetMimeTypeAsString(const FString& InMimeType)
{
	Request->AppendToHeader(TEXT("Content-Type"), InMimeType);
}

float UGenericHttpRequest::GetTimeout() const
{
	return Request->GetTimeout().GetValue();
}

void UGenericHttpRequest::SetTimeout(float InTimeoutSecs)
{
	Request->SetTimeout(InTimeoutSecs);
}

void UGenericHttpRequest::SetActivityTimeout(float InTimeoutSecs)
{
	Request->SetActivityTimeout(InTimeoutSecs);
}

void UGenericHttpRequest::ClearTimeout()
{
	Request->ClearTimeout();
}

void UGenericHttpRequest::ResetTimeoutStatus()
{
	Request->ResetTimeoutStatus();
}

bool UGenericHttpRequest::ProcessRequest()
{
	if (Request->GetContentType() == TEXT(""))
	{
		SetMimeType(EHttpMimeType::txt);
	}

	return Request->ProcessRequest();
}

void UGenericHttpRequest::CancelRequest()
{
	Request->CancelRequest();
}

void UGenericHttpRequest::OnHeaderReceivedInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, const FString& HeaderName, const FString& HeaderValue)
{
	OnRequestHeaderReceived.Broadcast(this, HeaderName, HeaderValue);
}

void UGenericHttpRequest::OnRequestProgressInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, uint64 BytesSent, uint64 BytesReceived)
{
	OnRequestProgress.Broadcast(this, BytesSent, BytesReceived);
}

void UGenericHttpRequest::OnRequestCompleteInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, bool bConnectedSuccessfully)
{
	OnRequestComplete.Broadcast(this, CreateResponse(RawRequest, RawResponse), bConnectedSuccessfully);
}

void UGenericHttpRequest::OnRequestWillRetryInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, float SecondsToRetry)
{
	OnRequestWillRetry.Broadcast(this, CreateResponse(RawRequest, RawResponse), SecondsToRetry);
}

UGenericHttpResponse* UGenericHttpRequest::CreateResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>& RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe>& RawResponse)
{
	UGenericHttpResponse* WrappedResponse = NewObject<UGenericHttpResponse>();
	WrappedResponse->InitInternal(this, RawResponse);
	return WrappedResponse;
}
