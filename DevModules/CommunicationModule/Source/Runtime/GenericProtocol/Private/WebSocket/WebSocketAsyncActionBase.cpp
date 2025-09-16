// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/WebSocketAsyncActionBase.h"

#include "WebSocket/GenericWebSocket.h"

void UWebSocketAsyncActionBase::SetReadyToDestroy()
{
	UnBindWebSocketDelegate();
	Super::SetReadyToDestroy();
}

void UWebSocketAsyncActionBase::InitWebSocket(UGenericWebSocket* InWebSocket)
{
	if (!IsValid(InWebSocket))
	{
		GenericLOG(GenericLogWebSocket, Error, TEXT("Invalid WebSocket"));
		return;
	}

	WebSocketInternal = InWebSocket;
	BindWebSocketDelegate();
}

UGenericWebSocket* UWebSocketAsyncActionBase::GetWebSocket()
{
	return WebSocketInternal;
}

void UWebSocketAsyncActionBase::BindWebSocketDelegate()
{
	if (IsValid(WebSocketInternal))
	{
		WebSocketInternal->OnConnectedEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnConnected);
		WebSocketInternal->OnConnectionErrorEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnConnectionError);
		WebSocketInternal->OnRawMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnRawMessage);
		WebSocketInternal->OnBinaryMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnBinaryMessage);
		WebSocketInternal->OnMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnMessage);
		WebSocketInternal->OnMessageSentEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnMessageSent);
		WebSocketInternal->OnCloseEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnClosed);
		WebSocketInternal->OnReStartedEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnReStarted);
		WebSocketInternal->OnReStartErrorEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnReStartError);
	}
}

void UWebSocketAsyncActionBase::UnBindWebSocketDelegate() const
{
	if (IsValid(WebSocketInternal))
	{
		WebSocketInternal->OnConnectedEvent.RemoveAll(this);
		WebSocketInternal->OnConnectionErrorEvent.RemoveAll(this);
		WebSocketInternal->OnRawMessageEvent.RemoveAll(this);
		WebSocketInternal->OnBinaryMessageEvent.RemoveAll(this);
		WebSocketInternal->OnMessageEvent.RemoveAll(this);
		WebSocketInternal->OnMessageSentEvent.RemoveAll(this);
		WebSocketInternal->OnCloseEvent.RemoveAll(this);
		WebSocketInternal->OnReStartedEvent.RemoveAll(this);
		WebSocketInternal->OnReStartErrorEvent.RemoveAll(this);
	}
}

void UWebSocketAsyncActionBase::HandleOnConnected(UGenericWebSocket* WebSocket)
{
	OnConnectedInternal(WebSocket);
}

void UWebSocketAsyncActionBase::HandleOnConnectionError(const FString& Error)
{
	OnConnectionErrorInternal(Error);
}

void UWebSocketAsyncActionBase::HandleOnRawMessage(const TArray<uint8>& Data, int32 BytesRemaining)
{
	OnRawMessageInternal(Data, BytesRemaining);
}

void UWebSocketAsyncActionBase::HandleOnBinaryMessage(const TArray<uint8>& Data, bool bIsLastFragment)
{
	OnBinaryMessageInternal(Data, bIsLastFragment);
}

void UWebSocketAsyncActionBase::HandleOnMessage(const FString& Message)
{
	OnMessageInternal(Message);
}

void UWebSocketAsyncActionBase::HandleOnMessageSent(const FString& Message)
{
	OnMessageSentInternal(Message);
}

void UWebSocketAsyncActionBase::HandleOnClosed(int32 Status, const FString& Reason, bool bWasClean)
{
	OnClosedInternal(Status, Reason, bWasClean);
}

void UWebSocketAsyncActionBase::HandleOnReStarted()
{
	OnReStartedInternal();
}

void UWebSocketAsyncActionBase::HandleOnReStartError(const FString& Error)
{
	OnReStartErrorInternal(Error);
}
