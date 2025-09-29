// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPISession_HTTP.h"
#include "HttpServerModule.h"
#include "IHttpRouter.h"
#include "NativeAPISettings.h"
#include "NativeAPITypes.h"
#include "NativeAPIUtilities.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool FNativeAPISession_HTTP::StartSession()
{
	const UNativeAPISettings* Settings = UNativeAPISettings::Get();
	check(Settings)

	if (!Settings->bSupportHTTP)
	{
		return false;
	}

	check(!HttpRouter.IsValid())

	FHttpServerModule& HttpServerModule = FHttpServerModule::Get();
	HttpRouter = FHttpServerModule::Get().GetHttpRouter(Settings->HTTPServerPort);

	if (!HttpRouter.IsValid())
	{
		return false;
	}

	const FHttpPath HttpPath(TEXT("/nativeapi"));

	const FHttpRequestHandler ThisHandler = FHttpRequestHandler::CreateLambda(
		[this](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete) -> bool
		{
			const FString JsonString(Request.Body.Num(), UTF8_TO_TCHAR(Request.Body.GetData()));

			TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(TEXT("NativeAPIResponse"), TEXT("application/json"));

			TSharedPtr<FJsonObject> JsonObject;
			const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

			FNativeAPIPayload Payload;
			if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
			{
				Response->Code = EHttpServerResponseCodes::BadRequest;
			}
			else if (FNativeAPIUtilities::ConvertNativeAPIJsonToPayload(JsonObject, Payload) && Payload.IsValid())
			{
				NotifyReceiveNativePayload(Payload);
				Response->Code = EHttpServerResponseCodes::Ok;
			}

			OnComplete(MoveTemp(Response));
			return true;
		}
	);
	// 路由路径
	RouteHandle = HttpRouter->BindRoute(HttpPath, EHttpServerRequestVerbs::VERB_GET, ThisHandler);

	HttpServerModule.StartAllListeners();
	return true;
}

void FNativeAPISession_HTTP::EndSession()
{
	if (HttpRouter.IsValid() && RouteHandle.IsValid())
	{
		HttpRouter->UnbindRoute(RouteHandle);
		HttpRouter.Reset();
	}
}
