// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Udp/UdpSocketAsyncActionBase.h"

#include "Udp/GenericUdpSocket.h"

void UUdpSocketAsyncActionBase::InitUdpSocket(UGenericUdpSocket* UdpSocket)
{
	if (!IsValid(UdpSocket))
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Invalid UdpSocket"));
		return;
	}

	UdpSocketInternal = UdpSocket;
}

void UUdpSenderAsyncActionBase::InitUdpSocket(UGenericUdpSocket* UdpSocket)
{
	Super::InitUdpSocket(UdpSocket);

	if (IsValid(UdpSocket))
	{
		UdpSocket->OnMessageSentEvent.AddDynamic(this, &UUdpSenderAsyncActionBase::HandleOnMessageSent);
		UdpSocket->OnMessageSentErrorEvent.AddDynamic(this, &UUdpSenderAsyncActionBase::HandleOnMessageSentError);
		UdpSocket->OnSenderClosedEvent.AddDynamic(this, &UUdpSenderAsyncActionBase::HandleOnSenderClosed);
	}
}

void UUdpSenderAsyncActionBase::SetReadyToDestroy()
{
	if (IsValid(GetUdpSocket()))
	{
		GetUdpSocket()->OnSenderConnectedEvent.RemoveAll(this);
		GetUdpSocket()->OnSenderConnectionErrorEvent.RemoveAll(this);
		GetUdpSocket()->OnMessageSentEvent.RemoveAll(this);
		GetUdpSocket()->OnMessageSentErrorEvent.RemoveAll(this);
		GetUdpSocket()->OnSenderClosedEvent.RemoveAll(this);
	}

	Super::SetReadyToDestroy();
}

void UUdpSenderAsyncActionBase::HandleOnMessageSent(const FString& Message)
{
	OnMessageSentInternal(Message);
}

void UUdpSenderAsyncActionBase::HandleOnMessageSentError(const FString& Message)
{
	OnMessageSentErrorInternal(Message);
}

void UUdpSenderAsyncActionBase::HandleOnSenderClosed(const FString& SendIp, const int32& SendPort)
{
	OnSenderClosedInternal(SendIp, SendPort);
}

void UUdpReceiverAsyncActionBase::InitUdpSocket(UGenericUdpSocket* UdpSocket)
{
	Super::InitUdpSocket(UdpSocket);

	if (IsValid(UdpSocket))
	{
		UdpSocket->OnReceiverConnectedEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverConnected);
		UdpSocket->OnReceiverConnectionErrorEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverConnectionError);
		UdpSocket->OnMessageEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnMessage);
		UdpSocket->OnReceiverClosedEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverClosed);
	}
}

void UUdpReceiverAsyncActionBase::SetReadyToDestroy()
{
	if (IsValid(GetUdpSocket()))
	{
		GetUdpSocket()->OnReceiverConnectedEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverConnected);
		GetUdpSocket()->OnReceiverConnectionErrorEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverConnectionError);
		GetUdpSocket()->OnMessageEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnMessage);
		GetUdpSocket()->OnReceiverClosedEvent.AddDynamic(this, &UUdpReceiverAsyncActionBase::HandleOnReceiverClosed);
	}

	Super::SetReadyToDestroy();
}

void UUdpReceiverAsyncActionBase::HandleOnReceiverConnected()
{
	OnReceiverConnectedInternal();
}

void UUdpReceiverAsyncActionBase::HandleOnReceiverConnectionError()
{
	OnReceiverConnectionErrorInternal();
}

void UUdpReceiverAsyncActionBase::HandleOnMessage(const FString& Message)
{
	OnMessageInternal(Message);
}

void UUdpReceiverAsyncActionBase::HandleOnReceiverClosed()
{
	OnReceiverClosedInternal();
}
