// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/AsyncAction/ConnectWebSocketAsyncAction.h"

#include "WebSocket/GenericWebSocket.h"

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::ConnectWebSocketWithConnection(UGenericWebSocket* InWebSocket, FWebSocketConnection InWebSocketConnect)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->InitWebSocket(InWebSocket);
	Action->GetWebSocket()->ConnectWithConnection(InWebSocketConnect);
	return Action;
}

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::ConnectWebSocketWithURL(UGenericWebSocket* InWebSocket, FString Host, int32 Port, EWebSocketProtocol Protocol, TMap<FString, FString> Headers)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->InitWebSocket(InWebSocket);
	Action->GetWebSocket()->ConnectWithURL(Host, Port, Protocol, Headers);
	return Action;
}

UConnectWebSocketAsyncAction* UConnectWebSocketAsyncAction::ConnectWebSocket(UGenericWebSocket* InWebSocket)
{
	UConnectWebSocketAsyncAction* Action = NewObject<UConnectWebSocketAsyncAction>();
	Action->InitWebSocket(InWebSocket);
	Action->GetWebSocket()->Connect();
	return Action;
}

void UConnectWebSocketAsyncAction::OnConnectedInternal(UGenericWebSocket* WebSocket)
{
	Super::OnConnectedInternal(WebSocket);
	OnConnected.Broadcast(WebSocket);
}

void UConnectWebSocketAsyncAction::OnConnectionErrorInternal(const FString& Error)
{
	Super::OnConnectionErrorInternal(Error);
	OnConnectionError.Broadcast(Error);
}
