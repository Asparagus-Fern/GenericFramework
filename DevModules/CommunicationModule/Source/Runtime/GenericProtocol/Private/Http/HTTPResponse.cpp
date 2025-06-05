// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/HTTPResponse.h"

#include "Interfaces/IHttpResponse.h"

void UHTTPResponse::InitInternal(TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse, const float& InRequestDuration)
{
	Response = InResponse;
	RequestDuration = InRequestDuration;
}

TMap<FString, FString> UHTTPResponse::GetHeaders() const
{
	if (!Response)
	{
		return TMap<FString, FString>();
	}

	TArray<FString> Headers = Response->GetAllHeaders();

	TMap<FString, FString> OutHeaders;

	for (FString& Header : Headers)
	{
		FString* Key = nullptr;
		FString* Value = nullptr;

		Header.Split(TEXT(": "), Key, Value, ESearchCase::CaseSensitive);

		if (Key && Value)
		{
			OutHeaders.Emplace(*Key, *Value);
		}
	}

	return OutHeaders;
}

void UHTTPResponse::GetContent(TArray<uint8>& OutContent) const
{
	if (Response)
	{
		OutContent = Response->GetContent();
	}
}

FString UHTTPResponse::GetContentAsString() const
{
	if (Response)
	{
		return Response->GetContentAsString();
	}
	return TEXT("");
}

int32 UHTTPResponse::GetContentLength() const
{
	return Response ? Response->GetContentLength() : 0;
}

FString UHTTPResponse::GetContentType() const
{
	return Response ? Response->GetContentType() : TEXT("");
}

FString UHTTPResponse::GetHeader(const FString& Key) const
{
	return Response ? Response->GetHeader(Key) : TEXT("");
}

int32 UHTTPResponse::GetResponseCode() const
{
	return Response ? Response->GetResponseCode() : -1;
}

FString UHTTPResponse::GetURL() const
{
	return Response ? Response->GetURL() : TEXT("");
}

FString UHTTPResponse::GetURLParameter(const FString& ParameterName) const
{
	return Response ? Response->GetURLParameter(ParameterName) : TEXT("");
}

float UHTTPResponse::GetElapsedTime() const
{
	return RequestDuration;
}
