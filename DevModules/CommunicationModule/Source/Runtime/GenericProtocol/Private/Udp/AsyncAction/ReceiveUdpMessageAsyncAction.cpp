// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/ReceiveUdpMessageAsyncAction.h"

UReceiveUdpMessageAsyncAction* UReceiveUdpMessageAsyncAction::ReceiveUdpMessage(UGenericUdpSocket* UdpSocket)
{
	UReceiveUdpMessageAsyncAction* Action = NewObject<UReceiveUdpMessageAsyncAction>();
	Action->InitUdpSocket(UdpSocket);
	if (IsValid(Action->GetUdpSocket()))
	{
		return Action;
	}

	return nullptr;
}

void UReceiveUdpMessageAsyncAction::OnMessageInternal(const FString& Message)
{
	Super::OnMessageInternal(Message);
	OnMessage.Broadcast(Message);
}
