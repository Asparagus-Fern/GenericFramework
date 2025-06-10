// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/AsyncAction/SendWebSocketMessageAsyncAction.h"

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendMessage(const FString& Message)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->GetWebSocket()->SendMessage(Message);
	return Action;
}

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendJsonMessage(UGenericJsonObject* JsonObject)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->GetWebSocket()->SendJsonMessage(JsonObject);
	return Action;
}

USendWebSocketMessageAsyncAction* USendWebSocketMessageAsyncAction::SendBinaryMessage(const TArray<uint8>& Message, const bool bIsBinary)
{
	USendWebSocketMessageAsyncAction* Action = NewObject<USendWebSocketMessageAsyncAction>();
	Action->GetWebSocket()->SendBinaryMessage(Message, bIsBinary);
	return Action;
}

void USendWebSocketMessageAsyncAction::OnMessageSentInternal(const FString& Message)
{
	Super::OnMessageSentInternal(Message);
	OnMessageSent.Broadcast(Message);
}
