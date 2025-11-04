// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Udp/GenericUdpSocket.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/UdpSocketReceiver.h"
#include "StaticFunctions/StaticFunctions_Convert.h"
#include "Udp/GenericUdpSocketBuilder.h"

UGenericUdpSocket* UGenericUdpSocket::CreateUdpSocket(UGenericUdpSocketBuilder* InBuilder)
{
	if (!InBuilder)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Builder Is InValid"))
		return nullptr;
	}

	UGenericUdpSocket* UdpSocket = NewObject<UGenericUdpSocket>();
	UdpSocket->UpdateUdpSocket(InBuilder);
	return UdpSocket;
}

void UGenericUdpSocket::UpdateUdpSocket(UGenericUdpSocketBuilder* InBuilder)
{
	if (!InBuilder)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("InBuilder Is InValid"))
		return;
	}

	Builder = InBuilder;
	SenderSocket = Builder->BuildSenderSocket();
	ReceiverSocket = Builder->BuildReceiverSocket();
}

bool UGenericUdpSocket::ConnectSender()
{
	if (!SenderSocket)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Sender Socket Is InValid, Use CreateUdpSocket To Create a Valid Udp Socket"));
		OnSenderConnectionErrorEvent.Broadcast(Builder->SendIp, Builder->SendPort);
		return false;
	}

	/* Connect Send Socket */
	TSharedRef<FInternetAddr> SendAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	SendAddr->SetIp(*Builder->SendIp, bIsValid);
	SendAddr->SetPort(Builder->SendPort);

	if (!bIsValid)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Send IP Is InValid"));
		OnSenderConnectionErrorEvent.Broadcast(Builder->SendIp, Builder->SendPort);
		return false;
	}

	if (SenderSocket->Connect(*SendAddr))
	{
		const ESocketConnectionState SocketConnectionState = SenderSocket->GetConnectionState();
		TSharedRef<FInternetAddr> SendBoundAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		SenderSocket->GetAddress(*SendBoundAddress);
		Builder->SendBoundIp = SendBoundAddress->ToString(false);
		Builder->SendBoundPort = SenderSocket->GetPortNo();

		GenericLOG(GenericLogUdp, Log, TEXT("Connect To Send Socket"));
		OnSenderConnectedEvent.Broadcast(Builder->SendBoundIp, Builder->SendBoundPort);

		return true;
	}

	GenericLOG(GenericLogUdp, Error, TEXT("Fail To Connect Send Socket"));
	OnSenderConnectionErrorEvent.Broadcast(Builder->SendIp, Builder->SendPort);
	return false;
}

bool UGenericUdpSocket::SendMessage(FString InMessage)
{
	if (!SenderSocket)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Socket Is InValid, Call CreateUdpSocket To Create a Valid Udp Socket"));
		OnMessageSentErrorEvent.Broadcast(InMessage);
		return false;
	}

	if (SenderSocket->GetConnectionState() != SCS_Connected)
	{
		GenericLOG(GenericLogUdp, Warning, TEXT("Socket Has Not Been Connected"));
		OnMessageSentErrorEvent.Broadcast(InMessage);
		return false;
	}

	int32 BytesSent = 0;
	TArray<uint8> ByteArray = FStaticFunctions_Convert::ToByteArray(InMessage);

	if (SenderSocket->Send(ByteArray.GetData(), ByteArray.Num(), BytesSent))
	{
		OnMessageSentEvent.Broadcast(InMessage);
		return true;
	}

	GenericLOG(GenericLogUdp, Error, TEXT("Fail To Send Message"));
	OnMessageSentErrorEvent.Broadcast(InMessage);
	return false;
}

bool UGenericUdpSocket::CloseSender()
{
	if (!SenderSocket)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Socket Is InValid, Use CreateUdpSocket To Create a Valid Udp Socket"));
		return false;
	}

	if (SenderSocket->Close())
	{
		GenericLOG(GenericLogUdp, Log, TEXT("Close Send Socket"));
		OnSenderClosedEvent.Broadcast(Builder->SendIp, Builder->SendPort);
		return true;
	}

	GenericLOG(GenericLogUdp, Error, TEXT("Fail To Close Send Socket"));
	return false;
}

bool UGenericUdpSocket::ConnectReceiver()
{
	if (!ReceiverSocket)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Socket Is InValid, Use CreateUdpSocket To Create a Valid Udp Socket"));
		OnReceiverConnectionErrorEvent.Broadcast();
		return false;
	}

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	FString ThreadName = FString::Printf(TEXT("UDP RECEIVER-GenericUdpSocket"));
	UDPReceiver = new FUdpSocketReceiver(ReceiverSocket, ThreadWaitTime, *ThreadName);
	UDPReceiver->OnDataReceived().BindUObject(this, &UGenericUdpSocket::HandleOnDataReceived);

	UDPReceiver->Start();
	OnReceiverConnectedEvent.Broadcast();
	return true;
}

bool UGenericUdpSocket::CloseReceiver()
{
	if (!ReceiverSocket)
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Socket Is InValid, Use CreateUdpSocket To Create a Valid Udp Socket"));
		return false;
	}

	if (!UDPReceiver)
	{
		GenericLOG(GenericLogUdp, Warning, TEXT("UDP Receiver Is InValid"));
		return false;
	}

	UDPReceiver->Stop();
	delete UDPReceiver;
	UDPReceiver = nullptr;

	if (ReceiverSocket->Close())
	{
		GenericLOG(GenericLogUdp, Error, TEXT("Close Receive Socket"));
		OnReceiverClosedEvent.Broadcast();
		return true;
	}

	GenericLOG(GenericLogUdp, Error, TEXT("Fail To Close Receive Socket"));
	return false;
}

void UGenericUdpSocket::HandleOnDataReceived(const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint) const
{
	TArray<uint8> Data;
	Data.AddUninitialized(DataPtr->TotalSize());
	DataPtr->Serialize(Data.GetData(), DataPtr->TotalSize());

	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	          {
		          OnMessageEvent.Broadcast(FStaticFunctions_Convert::ToString(Data));
	          }
	);
}
