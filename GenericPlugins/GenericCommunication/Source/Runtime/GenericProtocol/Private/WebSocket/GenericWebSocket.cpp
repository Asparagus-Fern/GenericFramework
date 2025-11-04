// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/GenericWebSocket.h"

#include "GenericJsonObject.h"
#include "IWebSocket.h"
#include "ProtocolType.h"
#include "WebSocketsModule.h"
#include "WebSocket/BPFunctions_WebSocket.h"

UGenericWebSocket::UGenericWebSocket(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UGenericWebSocket* UGenericWebSocket::CreateWebSocket()
{
	return NewObject<UGenericWebSocket>();
}

bool UGenericWebSocket::IsConnected() const
{
	return WebSocket.IsValid() ? WebSocket->IsConnected() : false;
}

void UGenericWebSocket::ConnectWithConnection(const FGenericWebSocketConnection& InWebSocketConnect)
{
	if (!InWebSocketConnect.IsValid())
	{
		GenericLOG(GenericLogWebSocket, Error, TEXT("Invalid WebSocketConnect"));
		return;
	}

	ConnectWithURL(InWebSocketConnect.Host, InWebSocketConnect.Port, InWebSocketConnect.Protocol, InWebSocketConnect.Headers);
}

void UGenericWebSocket::ConnectWithURL(const FString Host, const int32 Port, const EGenericWebSocketProtocol Protocol, const TMap<FString, FString>& Headers)
{
	if (!WebSocket.IsValid())
	{
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(UBPFunctions_WebSocket::GetWebSocketUrl(Host, Port, Protocol), ConvertToWebSocketProtocolString(Protocol), Headers);
	}

	if (IsConnected())
	{
		WebSocketCache = FWebSocketsModule::Get().CreateWebSocket(UBPFunctions_WebSocket::GetWebSocketUrl(Host, Port, Protocol), ConvertToWebSocketProtocolString(Protocol), Headers);
		Close();
	}
	else
	{
		Connect();
	}
}

void UGenericWebSocket::Connect()
{
	if (WebSocket.IsValid())
	{
		BindWebSocketDelegate();
		WebSocket->Connect();
	}
}

void UGenericWebSocket::Close(const int32 Code, FString Reason)
{
	if (IsConnected())
	{
		WebSocket->Close(Code, Reason);
	}
	else
	{
		GenericLOG(GenericLogWebSocket, Warning, TEXT("WebSocket is not connected"));
	}
}

void UGenericWebSocket::ReStart()
{
	if (WebSocket.IsValid())
	{
		if (IsConnected())
		{
			WebSocketCache = WebSocket;
			Close();
		}
		else
		{
			Connect();
		}
	}
}

void UGenericWebSocket::SendMessage(const FString& Message)
{
	if (IsConnected())
	{
		WebSocket->Send(Message);
	}
	else
	{
		GenericLOG(GenericLogWebSocket, Warning, TEXT("WebSocket is not connected"));
	}
}

void UGenericWebSocket::SendJsonMessage(UGenericJsonObject* JsonObject)
{
	if (IsValid(JsonObject))
	{
		GenericLOG(GenericLogWebSocket, Warning, TEXT("JsonObject Is InValid"));
		return;
	}

	FString Message;
	if (JsonObject->EncodeJson(Message))
	{
		SendMessage(Message);
	}
}

void UGenericWebSocket::SendBinaryMessage(const TArray<uint8>& Message, const bool bIsBinary)
{
	if (IsConnected())
	{
		WebSocket->Send(Message.GetData(), sizeof(uint8) * Message.Num(), bIsBinary);
	}
	else
	{
		GenericLOG(GenericLogWebSocket, Warning, TEXT("WebSocket is not connected"));
	}
}

void UGenericWebSocket::BindWebSocketDelegate()
{
	if (WebSocket.IsValid())
	{
		WebSocket->OnConnected().AddUObject(this, &UGenericWebSocket::OnConnected);
		WebSocket->OnConnectionError().AddUObject(this, &UGenericWebSocket::OnConnectionError);
		WebSocket->OnRawMessage().AddUObject(this, &UGenericWebSocket::OnRawMessage);
		WebSocket->OnBinaryMessage().AddUObject(this, &UGenericWebSocket::OnBinaryMessage);
		WebSocket->OnMessage().AddUObject(this, &UGenericWebSocket::OnMessage);
		WebSocket->OnMessageSent().AddUObject(this, &UGenericWebSocket::OnMessageSent);
		WebSocket->OnClosed().AddUObject(this, &UGenericWebSocket::OnClosed);
	}
}

void UGenericWebSocket::UnBindWebSocketDelegate() const
{
	if (WebSocket.IsValid())
	{
		WebSocket->OnConnected().RemoveAll(this);
		WebSocket->OnConnectionError().RemoveAll(this);
		WebSocket->OnRawMessage().RemoveAll(this);
		WebSocket->OnBinaryMessage().RemoveAll(this);
		WebSocket->OnMessage().RemoveAll(this);
		WebSocket->OnMessageSent().RemoveAll(this);
		WebSocket->OnClosed().RemoveAll(this);
	}
}

FString UGenericWebSocket::GetHost() const
{
	return WebSocketConnect.Host;
}

void UGenericWebSocket::SetHost(FString InHost)
{
	WebSocketConnect.Host = InHost;
}

int32 UGenericWebSocket::GetPort() const
{
	return WebSocketConnect.Port;
}

void UGenericWebSocket::SetPort(int32 InPort)
{
	WebSocketConnect.Port = InPort;
}

EGenericWebSocketProtocol UGenericWebSocket::GetProtocol() const
{
	return WebSocketConnect.Protocol;
}

void UGenericWebSocket::SetProtocol(EGenericWebSocketProtocol InProtocol)
{
	WebSocketConnect.Protocol = InProtocol;
}

void UGenericWebSocket::AddHeader(const FString& Header, const FString& Value)
{
	WebSocketConnect.Headers.Add(Header, Value);
}

void UGenericWebSocket::AddHeaders(TMap<FString, FString> Headers)
{
	WebSocketConnect.Headers.Append(Headers);
}

void UGenericWebSocket::RemoveHeader(const FString& Header)
{
	WebSocketConnect.Headers.Remove(Header);
}

void UGenericWebSocket::RemoveHeaders(TArray<FString> Headers)
{
	for (auto& Header : Headers)
	{
		RemoveHeader(Header);
	}
}

TMap<FString, FString> UGenericWebSocket::GetHeaders()
{
	return WebSocketConnect.Headers;
}

void UGenericWebSocket::SetHeaders(TMap<FString, FString> Headers)
{
	WebSocketConnect.Headers = Headers;
}

void UGenericWebSocket::OnConnected()
{
	OnConnectedEvent.Broadcast(this);

	if (bBroadcastReStart)
	{
		bBroadcastReStart = false;
		OnReStartedEvent.Broadcast();
	}
}

void UGenericWebSocket::OnConnectionError(const FString& Error)
{
	OnConnectionErrorEvent.Broadcast(Error);

	if (bBroadcastReStart)
	{
		bBroadcastReStart = false;
		OnReStartErrorEvent.Broadcast(Error);
	}
}

void UGenericWebSocket::OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
{
	const TArray<uint8> ArrayData(static_cast<const uint8*>(Data), Size / sizeof(uint8));
	OnRawMessageEvent.Broadcast(ArrayData, BytesRemaining);
}

void UGenericWebSocket::OnBinaryMessage(const void* Data, SIZE_T Size, bool bIsLastFragment)
{
	const TArray<uint8> ArrayData(static_cast<const uint8*>(Data), Size / sizeof(uint8));
	OnBinaryMessageEvent.Broadcast(ArrayData, bIsLastFragment);
}

void UGenericWebSocket::OnMessage(const FString& Message)
{
	OnMessageEvent.Broadcast(Message);
}

void UGenericWebSocket::OnMessageSent(const FString& Message)
{
	OnMessageSentEvent.Broadcast(Message);
}

void UGenericWebSocket::OnClosed(int32 Status, const FString& Reason, bool bWasClean)
{
	OnCloseEvent.Broadcast(Status, Reason, bWasClean);
	UnBindWebSocketDelegate();

	if (WebSocketCache.IsValid())
	{
		WebSocket = WebSocketCache;
		WebSocketCache = nullptr;
		Connect();
	}
}
