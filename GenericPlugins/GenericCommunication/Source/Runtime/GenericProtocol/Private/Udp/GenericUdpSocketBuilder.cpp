// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Udp/GenericUdpSocketBuilder.h"

#include "Common/UdpSocketBuilder.h"

FSocket* UGenericUdpSocketBuilder::BuildSenderSocket()
{
	if (bEnableSend)
	{
		FUdpSocketBuilder* UdpSocketBuilder = new FUdpSocketBuilder(SocketName);
		Build(UdpSocketBuilder);

		UdpSocketBuilder->WithSendBufferSize(SendBufferSize);

		return UdpSocketBuilder->Build();
	}

	return nullptr;
}

FSocket* UGenericUdpSocketBuilder::BuildReceiverSocket()
{
	if (bEnableReceive)
	{
		FUdpSocketBuilder* UdpSocketBuilder = new FUdpSocketBuilder(SocketName);
		Build(UdpSocketBuilder);

		UdpSocketBuilder->WithReceiveBufferSize(ReceiveBufferSize);

		FIPv4Address Addr;
		FIPv4Address::Parse(ReceiveIp, Addr);
		FIPv4Endpoint Endpoint(Addr, ReceivePort);
		UdpSocketBuilder->BoundToEndpoint(Endpoint);

		return UdpSocketBuilder->Build();
	}

	return nullptr;
}

void UGenericUdpSocketBuilder::Build(FUdpSocketBuilder* UdpSocketBuilder) const
{
	if (bIsBlocking)
	{
		UdpSocketBuilder->AsBlocking();
	}
	else
	{
		UdpSocketBuilder->AsNonBlocking();
	}

	if (bEnableReusable)
	{
		UdpSocketBuilder->AsReusable();
	}

#if PLATFORM_SUPPORTS_UDP_MULTICAST_GROUP
	if (bEnableBroadcast)
	{
		UdpSocketBuilder->WithBroadcast();
	}

	if (bEnableMulticastLoopback)
	{
		UdpSocketBuilder->WithMulticastLoopback();
	}
#endif
}

void UGenericUdpSocketBuilder::SetIsBlocking(const bool IsBlocking)
{
	bIsBlocking = IsBlocking;
}

void UGenericUdpSocketBuilder::SetEnableReusable(bool EnableReusable)
{
	bEnableReusable = EnableReusable;
}

void UGenericUdpSocketBuilder::SetEnableBroadcast(bool EnableBroadcast)
{
	bEnableBroadcast = EnableBroadcast;
}

void UGenericUdpSocketBuilder::SetEnableMulticastLoopback(bool EnableMulticastLoopback)
{
	bEnableMulticastLoopback = EnableMulticastLoopback;
}
