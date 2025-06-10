// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/WebSocketAsyncActionBase.h"

#include "WebSocket/GenericWebSocket.h"

UWebSocketAsyncActionBase::UWebSocketAsyncActionBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WebSocket = UGenericWebSocket::CreateWebSocket();
	BindWebSocketDelegate();
}

void UWebSocketAsyncActionBase::SetReadyToDestroy()
{
	UnBindWebSocketDelegate();
	Super::SetReadyToDestroy();
}

void UWebSocketAsyncActionBase::BindWebSocketDelegate()
{
	if (IsValid(WebSocket))
	{
		WebSocket->OnConnectedEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnConnected);
		WebSocket->OnConnectionErrorEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnConnectionError);
		WebSocket->OnRawMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnRawMessage);
		WebSocket->OnBinaryMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnBinaryMessage);
		WebSocket->OnMessageEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnMessage);
		WebSocket->OnMessageSentEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnMessageSent);
		WebSocket->OnCloseEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnClosed);
		WebSocket->OnReStartedEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnReStarted);
		WebSocket->OnReStartErrorEvent.AddDynamic(this, &UWebSocketAsyncActionBase::HandleOnReStartError);
	}
}

void UWebSocketAsyncActionBase::UnBindWebSocketDelegate() const
{
	if (IsValid(WebSocket))
	{
		WebSocket->OnConnectedEvent.RemoveAll(this);
		WebSocket->OnConnectionErrorEvent.RemoveAll(this);
		WebSocket->OnRawMessageEvent.RemoveAll(this);
		WebSocket->OnBinaryMessageEvent.RemoveAll(this);
		WebSocket->OnMessageEvent.RemoveAll(this);
		WebSocket->OnMessageSentEvent.RemoveAll(this);
		WebSocket->OnCloseEvent.RemoveAll(this);
		WebSocket->OnReStartedEvent.RemoveAll(this);
		WebSocket->OnReStartErrorEvent.RemoveAll(this);
	}
}

void UWebSocketAsyncActionBase::HandleOnConnected()
{
	OnConnectedInternal();
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

UGenericWebSocket* UWebSocketAsyncActionBase::GetWebSocket()
{
	return WebSocket;
}

void UWebSocketAsyncActionBase::SetWebSocket(UGenericWebSocket* InWebSocket)
{
	if (WebSocket == InWebSocket)
	{
		return;
	}

	if (!IsValid(InWebSocket))
	{
		GenericLOG(GenericLogWebSocket, Error, TEXT("Invalid WebSocket"));
		return;
	}

	UnBindWebSocketDelegate();
	WebSocket = InWebSocket;
	BindWebSocketDelegate();
}
