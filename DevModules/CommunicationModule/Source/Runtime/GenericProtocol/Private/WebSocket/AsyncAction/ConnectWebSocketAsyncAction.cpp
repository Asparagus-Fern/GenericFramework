// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/AsyncAction/ConnectWebSocketAsyncAction.h"

#include "WebSocket/GenericWebSocket.h"

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::ConnectWithConnection(FWebSocketConnection InWebSocketConnect)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->GetWebSocket()->ConnectWithConnection(InWebSocketConnect);
	return Action;
}

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::ConnectWithURL(FString Host, int32 Port, EWebSocketProtocol Protocol, TMap<FString, FString> Headers)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->GetWebSocket()->ConnectWithURL(Host, Port, Protocol, Headers);
	return Action;
}

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::Connect(UGenericWebSocket* InWebSocket)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->SetWebSocket(InWebSocket);
	Action->GetWebSocket()->Connect();
	return Action;
}

void UConnectWebSocketAsyncAction::OnConnectedInternal()
{
	Super::OnConnectedInternal();
	OnConnected.Broadcast();
}

void UConnectWebSocketAsyncAction::OnConnectionErrorInternal(const FString& Error)
{
	Super::OnConnectionErrorInternal(Error);
	OnConnectionError.Broadcast(Error);
}
