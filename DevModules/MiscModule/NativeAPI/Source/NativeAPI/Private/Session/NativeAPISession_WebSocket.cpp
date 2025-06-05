// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPISession_WebSocket.h"
#include "NativeAPISettings.h"
#include "NativeAPITypes.h"
#include "NativeAPIUtilities.h"
#include "WebSocketsModule.h"
#include "Debug/DebugType.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_WEBSOCKETS
#include "IWebSocket.h"
#endif

FNativeAPISession_WebSocket::FNativeAPISession_WebSocket()
	: WebSocket(nullptr)
{
}

bool FNativeAPISession_WebSocket::StartSession()
{
	const UNativeAPISettings* Settings = UNativeAPISettings::Get();
	check(Settings)
	if (!Settings->bSupportWebSocket)
	{
		return false;
	}

	Connect = Settings->Connect;

	if (Connect.IsValid())
	{
#if WITH_WEBSOCKETS
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Connect.GetUrl(), EnumToString(Connect.Protocol), Connect.Headers);

		if (WebSocket.IsValid())
		{
			WebSocket->OnConnected().AddRaw(this, &FNativeAPISession_WebSocket::HandleOnWebSocketConnection);
			WebSocket->OnConnectionError().AddRaw(this, &FNativeAPISession_WebSocket::HandleOnWebSocketConnectionError);
			WebSocket->OnMessage().AddRaw(this, &FNativeAPISession_WebSocket::HandleOnWebSocketMessage);
			WebSocket->Connect();
			return true;
		}
#endif
		return false;
	}

	return false;
}

void FNativeAPISession_WebSocket::EndSession()
{
#if WITH_WEBSOCKETS
	if (WebSocket.IsValid() && WebSocket->IsConnected())
	{
		WebSocket->Close();
		WebSocket.Reset();
	}
#endif
}

void FNativeAPISession_WebSocket::HandleOnWebSocketConnection()
{
	GenericLOG(LogTemp, Warning, TEXT("Native API WebSocket Session Connect, [URL] %s"), *Connect.GetUrl())
}

void FNativeAPISession_WebSocket::HandleOnWebSocketConnectionError(const FString& Error)
{
	GenericLOG(LogTemp, Warning, TEXT("Native API WebSocket Session Connect Error, [URL] %s, [Error] %s"), *Connect.GetUrl(), *Error);
	WebSocket.Reset();
}

void FNativeAPISession_WebSocket::HandleOnWebSocketMessage(const FString& InMessage)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InMessage);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		GenericLOG(LogTemp, Warning, TEXT("无效的NativeAPI WebSocket 消息!"))
		return;
	}

	FNativeAPIPayload Payload;
	if (!FNativeAPIUtilities::ConvertNativeAPIJsonToPayload(JsonObject, Payload) || !Payload.IsValid())
	{
		GenericLOG(LogTemp, Warning, TEXT("无法转换 WebSocket 信息 为 Native API Payload!"))
		return;
	}

	NotifyReceiveNativePayload(Payload);
}
