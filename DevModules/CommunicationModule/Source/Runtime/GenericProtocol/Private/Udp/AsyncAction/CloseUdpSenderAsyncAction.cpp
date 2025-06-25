// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/CloseUdpSenderAsyncAction.h"

UCloseUdpSenderAsyncAction* UCloseUdpSenderAsyncAction::CloseUdpSender(UGenericUdpSocket* UdpSocket, bool& Result)
{
	UCloseUdpSenderAsyncAction* Action = NewObject<UCloseUdpSenderAsyncAction>();
	Action->InitUdpSocket(UdpSocket);
	if (IsValid(Action->GetUdpSocket()))
	{
		Result = Action->GetUdpSocket()->CloseSender();
		return Action;
	}

	return nullptr;
}

void UCloseUdpSenderAsyncAction::OnSenderClosedInternal(const FString& SendIp, const int32& SendPort)
{
	Super::OnSenderClosedInternal(SendIp, SendPort);
	OnSenderClosed.Broadcast(SendIp, SendPort);
}
