// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/GenericHttpResponse.h"

#include "Http/GenericHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Runtime/GenericJson/Public/GenericJsonObject.h"

void UGenericHttpResponse::InitInternal(TWeakObjectPtr<UGenericHttpRequest> InRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> InResponse)
{
	Request = InRequest;
	Response = InResponse;
}

TMap<FString, FString> UGenericHttpResponse::GetHeaders() const
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

void UGenericHttpResponse::GetContent(TArray<uint8>& OutContent) const
{
	if (Response)
	{
		OutContent = Response->GetContent();
	}
}

FString UGenericHttpResponse::GetContentAsString() const
{
	if (Response)
	{
		return Response->GetContentAsString();
	}
	return TEXT("");
}

UGenericJsonObject* UGenericHttpResponse::GetContentAsJson()
{
	if (!JsonObject)
	{
		JsonObject = NewObject<UGenericJsonObject>();
	}

	JsonObject->DecodeJson(Response->GetContentAsString());
	return JsonObject;
}

int32 UGenericHttpResponse::GetContentLength() const
{
	return Response ? Response->GetContentLength() : 0;
}

FString UGenericHttpResponse::GetContentType() const
{
	return Response ? Response->GetContentType() : TEXT("");
}

FString UGenericHttpResponse::GetHeader(const FString& Key) const
{
	return Response ? Response->GetHeader(Key) : TEXT("");
}

int32 UGenericHttpResponse::GetResponseCode() const
{
	return Response ? Response->GetResponseCode() : -1;
}

FString UGenericHttpResponse::GetURL() const
{
	return Response ? Response->GetURL() : TEXT("");
}

FString UGenericHttpResponse::GetURLParameter(const FString& ParameterName) const
{
	return Response ? Response->GetURLParameter(ParameterName) : TEXT("");
}

float UGenericHttpResponse::GetElapsedTime() const
{
	return Request.IsValid() ? Request.Get()->GetElapsedTime() : 0.f;
}

UGenericHttpRequest* UGenericHttpResponse::GetRequest() const
{
	return Request.IsValid() ? Request.Get() : nullptr;
}
