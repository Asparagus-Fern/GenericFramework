// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/CloseUdpReceiverAsyncAction.h"

UCloseUdpReceiverAsyncAction* UCloseUdpReceiverAsyncAction::CloseUdpReceiver(UGenericUdpSocket* UdpSocket, bool& Result)
{
	UCloseUdpReceiverAsyncAction* Action = NewObject<UCloseUdpReceiverAsyncAction>();
	Action->InitUdpSocket(UdpSocket);
	if (IsValid(Action->GetUdpSocket()))
	{
		Result = Action->GetUdpSocket()->CloseReceiver();
		return Action;
	}

	return nullptr;
}

void UCloseUdpReceiverAsyncAction::OnReceiverClosedInternal()
{
	Super::OnReceiverClosedInternal();
	OnReceiverClosed.Broadcast();
}
