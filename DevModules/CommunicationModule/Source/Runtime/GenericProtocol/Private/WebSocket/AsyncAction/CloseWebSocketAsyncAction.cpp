// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/AsyncAction/CloseWebSocketAsyncAction.h"

#include "WebSocket/GenericWebSocket.h"

UCloseWebSocketAsyncAction* UCloseWebSocketAsyncAction::Close(int32 Code, FString Reason)
{
	UCloseWebSocketAsyncAction* Action = NewObject<UCloseWebSocketAsyncAction>();
	Action->GetWebSocket()->Close(Code, Reason);
	return Action;
}

void UCloseWebSocketAsyncAction::OnClosedInternal(int32 Status, const FString& Reason, bool bWasClean)
{
	Super::OnClosedInternal(Status, Reason, bWasClean);
	OnClosed.Broadcast(Status, Reason, bWasClean);
}
