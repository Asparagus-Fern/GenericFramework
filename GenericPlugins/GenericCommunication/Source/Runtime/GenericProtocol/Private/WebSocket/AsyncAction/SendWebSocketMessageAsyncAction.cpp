// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/AsyncAction/SendWebSocketMessageAsyncAction.h"

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendWebSocketMessage(UGenericWebSocket* WebSocket, const FString& Message)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->InitWebSocket(WebSocket);
	Action->GetWebSocket()->SendMessage(Message);
	return Action;
}

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendWebSocketJsonMessage(UGenericWebSocket* WebSocket, UGenericJsonObject* JsonObject)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->InitWebSocket(WebSocket);
	Action->GetWebSocket()->SendJsonMessage(JsonObject);
	return Action;
}

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendWebSocketBinaryMessage(UGenericWebSocket* WebSocket, const TArray<uint8>& Message, const bool bIsBinary)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->InitWebSocket(WebSocket);
	Action->GetWebSocket()->SendBinaryMessage(Message, bIsBinary);
	return Action;
}

void USendWebSocketMessageAsyncAction::OnMessageSentInternal(const FString& Message)
{
	Super::OnMessageSentInternal(Message);
	OnMessageSent.Broadcast(Message);
}
