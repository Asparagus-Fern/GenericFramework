// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/ConnectUdpReceiverAsyncAction.h"

UConnectUdpReceiverAsyncAction* UConnectUdpReceiverAsyncAction::ConnectUdpReceiver(UGenericUdpSocket* UdpSocket, bool& Result)
{
	UConnectUdpReceiverAsyncAction* Action = NewObject<UConnectUdpReceiverAsyncAction>();
	Action->InitUdpSocket(UdpSocket);
	if (IsValid(Action->GetUdpSocket()))
	{
		Result = Action->GetUdpSocket()->ConnectReceiver();
		return Action;
	}

	return nullptr;
}

void UConnectUdpReceiverAsyncAction::OnReceiverConnectedInternal()
{
	Super::OnReceiverConnectedInternal();
	OnReceiverConnected.Broadcast();
}

void UConnectUdpReceiverAsyncAction::OnReceiverConnectionErrorInternal()
{
	Super::OnReceiverConnectionErrorInternal();
	OnReceiverConnectionError.Broadcast();
}
