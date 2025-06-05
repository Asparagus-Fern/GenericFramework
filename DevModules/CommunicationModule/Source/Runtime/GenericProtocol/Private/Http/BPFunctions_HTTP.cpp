// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Http/BPFunctions_HTTP.h"

#include "HttpModule.h"
#include "Windows/WindowsPlatformHttp.h"

EHttpVerb UBPFunctions_HTTP::BP_ConvertStringVerbToEnum(FString InVerb)
{
	return ConvertStringVerbToEnum(InVerb);
}

FString UBPFunctions_HTTP::BP_ConvertEnumVerbToString(EHttpVerb InVerb)
{
	return ConvertEnumVerbToString(InVerb);
}

EHttpMimeType UBPFunctions_HTTP::BP_ConvertStringMimeTypeToEnum(FString InMimeType)
{
	return ConvertStringMimeTypeToEnum(InMimeType);
}

FString UBPFunctions_HTTP::BP_ConvertEnumMimeTypeToString(EHttpMimeType InMimeType)
{
	return ConvertEnumMimeTypeToString(InMimeType);
}

EHttpResponseCode UBPFunctions_HTTP::BP_ConvertToResponseCodeEnum(int32 InCode)
{
	return ConvertToResponseCodeEnum(InCode);
}

int32 UBPFunctions_HTTP::BP_ConvertToResponseCode(EHttpResponseCode InCode)
{
	return ConvertToResponseCode(InCode);
}

int32 UBPFunctions_HTTP::GetHttpMaxConnectionsPerServer()
{
	return FHttpModule::Get().GetHttpMaxConnectionsPerServer();
}

FString UBPFunctions_HTTP::GetProxyAddress()
{
	return FHttpModule::Get().GetProxyAddress();
}

int32 UBPFunctions_HTTP::GetMaxReadBufferSize()
{
	return FHttpModule::Get().GetMaxReadBufferSize();
}

void UBPFunctions_HTTP::AddDefaultHeader(const FString& HeaderName, const FString& HeaderValue)
{
	return FHttpModule::Get().AddDefaultHeader(HeaderName, HeaderValue);
}

void UBPFunctions_HTTP::SetProxyAddress(const FString& InProxyAddress)
{
	return FHttpModule::Get().SetProxyAddress(InProxyAddress);
}

void UBPFunctions_HTTP::SetMaxReadBufferSize(const int32 SizeInBytes)
{
	return FHttpModule::Get().SetMaxReadBufferSize(SizeInBytes);
}

void UBPFunctions_HTTP::SetHttpThreadIdleMinimumSleepTimeInSeconds(const float Time)
{
	return FHttpModule::Get().SetHttpThreadIdleMinimumSleepTimeInSeconds(Time);
}

void UBPFunctions_HTTP::SetHttpThreadIdleFrameTimeInSeconds(const float Time)
{
	return FHttpModule::Get().SetHttpThreadIdleFrameTimeInSeconds(Time);
}

void UBPFunctions_HTTP::SetHttpThreadActiveMinimumSleepTimeInSeconds(const float Time)
{
	return FHttpModule::Get().SetHttpThreadActiveMinimumSleepTimeInSeconds(Time);
}

void UBPFunctions_HTTP::SetHttpThreadActiveFrameTimeInSeconds(const float Time)
{
	return FHttpModule::Get().SetHttpThreadActiveFrameTimeInSeconds(Time);
}

void UBPFunctions_HTTP::SetHttpDelayTime(const float Delay)
{
	return FHttpModule::Get().SetHttpDelayTime(Delay);
}

FString UBPFunctions_HTTP::AddParametersToUrl(FString InUrl, const TMap<FString, FString>& Parameters)
{
	const int32 ParametersCount = Parameters.Num();

	if (ParametersCount < 1)
	{
		return InUrl;
	}

	InUrl += TEXT("?");

	int32 i = 0;
	for (auto It = Parameters.begin(); It != Parameters.end(); ++i, ++It)
	{
		InUrl += FPlatformHttp::UrlEncode(It->Key) + TEXT("=") + FPlatformHttp::UrlEncode(It->Value);
		if (i != ParametersCount - 1)
		{
			InUrl += TEXT("&");
		}
	}

	return InUrl; 
}
