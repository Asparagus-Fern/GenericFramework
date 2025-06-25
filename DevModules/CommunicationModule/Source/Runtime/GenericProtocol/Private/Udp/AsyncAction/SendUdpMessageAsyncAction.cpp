// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/SendUdpMessageAsyncAction.h"

USendUdpMessageAsyncAction* USendUdpMessageAsyncAction::SendUdpMessage(UGenericUdpSocket* UdpSocket, FString InMessage, bool& Result)
{
	USendUdpMessageAsyncAction* Action = NewObject<USendUdpMessageAsyncAction>();
	Action->InitUdpSocket(UdpSocket);
	if (IsValid(Action->GetUdpSocket()))
	{
		Result = Action->GetUdpSocket()->SendMessage(InMessage);
		return Action;
	}

	return nullptr;
}

void USendUdpMessageAsyncAction::OnMessageSentInternal(const FString& Message)
{
	Super::OnMessageSentInternal(Message);
	OnMessageSent.Broadcast(Message);
}

void USendUdpMessageAsyncAction::OnMessageSentErrorInternal(const FString& Message)
{
	Super::OnMessageSentErrorInternal(Message);
	OnMessageSentError.Broadcast(Message);
}
