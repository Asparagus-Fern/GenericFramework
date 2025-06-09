// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/HTTPRequest.h"

#include "HttpModule.h"
#include "Http/BPFunctions_HTTP.h"
#include "Http/HTTPResponse.h"

UHTTPRequest::UHTTPRequest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Request = FHttpModule::Get().CreateRequest();
	if (Request.IsValid())
	{
		Request->OnHeaderReceived().BindUObject(this, &UHTTPRequest::OnHeaderReceivedInternal);
		Request->OnRequestProgress64().BindUObject(this, &UHTTPRequest::OnRequestProgressInternal);
		Request->OnProcessRequestComplete().BindUObject(this, &UHTTPRequest::OnRequestCompleteInternal);
		Request->OnRequestWillRetry().BindUObject(this, &UHTTPRequest::OnRequestWillRetryInternal);
	}
}

UHTTPRequest* UHTTPRequest::CreateHTTPRequest()
{
	return NewObject<UHTTPRequest>();
}

void UHTTPRequest::GetContent(TArray<uint8>& OutContent) const
{
	OutContent = Request->GetContent();
}

void UHTTPRequest::SetContent(const TArray<uint8>& InContent)
{
	Request->SetContent(InContent);
}

FString UHTTPRequest::GetContentAsString() const
{
	const TArray<uint8>& Content = Request->GetContent();
	return BytesToString(Content.GetData(), Content.Num());
}

void UHTTPRequest::SetContentAsString(const FString& InContent)
{
	Request->SetContentAsString(InContent);
}

void UHTTPRequest::SetContentAsStreamedFile(const FString& InFileName, bool& bFileValid)
{
	bFileValid = Request->SetContentAsStreamedFile(InFileName);
}

int32 UHTTPRequest::GetContentLength() const
{
	return Request->GetContentLength();
}

FString UHTTPRequest::GetContentType() const
{
	return Request->GetContentType();
}

float UHTTPRequest::GetElapsedTime() const
{
	return Request->GetContentLength();
}

FString UHTTPRequest::GetHeader(const FString& Key) const
{
	return Request->GetContentType();
}

void UHTTPRequest::SetHeader(const FString& Key, const FString& Value)
{
	Request->SetHeader(Key, Value);
}

TMap<FString, FString> UHTTPRequest::GetHeaders() const
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

void UHTTPRequest::SetHeaders(const TMap<FString, FString>& Headers)
{
	for (const auto& Header : Headers)
	{
		Request->SetHeader(Header.Key, Header.Value);
	}
}

void UHTTPRequest::AppendToHeader(const FString& Key, const FString& Value)
{
	Request->AppendToHeader(Key, Value);
}

EHttpRequestStatusBP UHTTPRequest::GetStatus() const
{
	return ConvertToHttpRequestStatusBP(Request->GetStatus());
}

FString UHTTPRequest::GetURL() const
{
	return Request->GetURL();
}

void UHTTPRequest::SetURL(FString InURL)
{
	Request->SetURL(InURL);
}

void UHTTPRequest::SetURLWithParameter(FString InURL, const TMap<FString, FString>& InParameters)
{
	SetURL(UBPFunctions_HTTP::AddParametersToUrl(InURL, InParameters));
}

FString UHTTPRequest::GetURLParameter(const FString& InParameterName) const
{
	return Request->GetURLParameter(InParameterName);
}

FString UHTTPRequest::GetVerb() const
{
	return Request->GetVerb();
}

void UHTTPRequest::SetVerb(FString InVerb)
{
	Request->SetVerb(InVerb);
}

EHttpVerb UHTTPRequest::GetVerbAsEnum() const
{
	return ConvertStringVerbToEnum(Request->GetVerb());
}

void UHTTPRequest::SetVerbAsEnum(const EHttpVerb InVerb)
{
	Request->SetVerb(ConvertEnumVerbToString(InVerb));
}

void UHTTPRequest::SetMimeType(const EHttpMimeType InMimeType)
{
	Request->AppendToHeader(TEXT("Content-Type"), CreateHttpMimeType(InMimeType));
}

void UHTTPRequest::SetMimeTypeAsString(const FString& InMimeType)
{
	Request->AppendToHeader(TEXT("Content-Type"), InMimeType);
}

float UHTTPRequest::GetTimeout() const
{
	return Request->GetTimeout().GetValue();
}

void UHTTPRequest::SetTimeout(float InTimeoutSecs)
{
	Request->SetTimeout(InTimeoutSecs);
}

void UHTTPRequest::SetActivityTimeout(float InTimeoutSecs)
{
	Request->SetActivityTimeout(InTimeoutSecs);
}

void UHTTPRequest::ClearTimeout()
{
	Request->ClearTimeout();
}

void UHTTPRequest::ResetTimeoutStatus()
{
	Request->ResetTimeoutStatus();
}

bool UHTTPRequest::ProcessRequest()
{
	if (Request->GetContentType() == TEXT(""))
	{
		SetMimeType(EHttpMimeType::txt);
	}

	return Request->ProcessRequest();
}

void UHTTPRequest::CancelRequest()
{
	Request->CancelRequest();
}

void UHTTPRequest::OnHeaderReceivedInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, const FString& HeaderName, const FString& HeaderValue)
{
	OnRequestHeaderReceived.Broadcast(this, HeaderName, HeaderValue);
}

void UHTTPRequest::OnRequestProgressInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, uint64 BytesSent, uint64 BytesReceived)
{
	OnRequestProgress.Broadcast(this, BytesSent, BytesReceived);
}

void UHTTPRequest::OnRequestCompleteInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, bool bConnectedSuccessfully)
{
	OnRequestComplete.Broadcast(this, CreateResponse(RawRequest, RawResponse), bConnectedSuccessfully);
}

void UHTTPRequest::OnRequestWillRetryInternal(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> RawResponse, float SecondsToRetry)
{
	OnRequestWillRetry.Broadcast(this, CreateResponse(RawRequest, RawResponse), SecondsToRetry);
}

UHTTPResponse* UHTTPRequest::CreateResponse(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>& RawRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe>& RawResponse)
{
	UHTTPResponse* WrappedResponse = NewObject<UHTTPResponse>();
	WrappedResponse->InitInternal(this, RawResponse);
	return WrappedResponse;
}
