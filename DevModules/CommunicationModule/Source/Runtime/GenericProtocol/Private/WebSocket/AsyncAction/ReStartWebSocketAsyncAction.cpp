// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WebSocket/AsyncAction/ReStartWebSocketAsyncAction.h"

UReStartWebSocketAsyncAction* UReStartWebSocketAsyncAction::ReStart()
{
	UReStartWebSocketAsyncAction* Action = NewObject<UReStartWebSocketAsyncAction>();
	Action->GetWebSocket()->ReStart();
	return Action;
}

void UReStartWebSocketAsyncAction::OnReStartedInternal()
{
	Super::OnReStartedInternal();
	OnReStarted.Broadcast();
}

void UReStartWebSocketAsyncAction::OnReStartErrorInternal(const FString& Error)
{
	Super::OnReStartErrorInternal(Error);
	OnReStartError.Broadcast(Error);
}
