// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/AsyncAction/ConnectUdpSenderAsyncAction.h"

UConnectUdpSenderAsyncAction* UConnectUdpSenderAsyncAction::ConnectUdpSender(UGenericUdpSocket* UdpSocket, bool& Result)
{
	UConnectUdpSenderAsyncAction* Action = NewObject<UConnectUdpSenderAsyncAction>();

	if (IsValid(UdpSocket))
	{
		UdpSocket->OnSenderConnectedEvent.AddUniqueDynamic(Action, &UConnectUdpSenderAsyncAction::HandleOnSenderConnected);
		UdpSocket->OnSenderConnectionErrorEvent.AddUniqueDynamic(Action, &UConnectUdpSenderAsyncAction::HandleOnSenderConnectionError);
		Result = UdpSocket->ConnectSender();
	}

	return Action;
}

void UConnectUdpSenderAsyncAction::HandleOnSenderConnected(const FString& SendBoundIp, const int32& SendBoundPort)
{
	OnSenderConnected.Broadcast(SendBoundIp, SendBoundPort);
}

void UConnectUdpSenderAsyncAction::HandleOnSenderConnectionError(const FString& SendIp, const int32& SendPort)
{
	OnSenderConnectionError.Broadcast(SendIp, SendPort);
}
