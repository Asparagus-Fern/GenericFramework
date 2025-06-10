// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/BPFunctions_WebSocket.h"

#include "BPFunctions_Protocol.h"

EWebSocketProtocol UBPFunctions_WebSocket::BP_ConvertToWebSocketProtocolEnum(FString InProtocol)
{
	return ConvertToWebSocketProtocolEnum(InProtocol);
}

FString UBPFunctions_WebSocket::BP_ConvertToWebSocketProtocolString(EWebSocketProtocol InProtocol)
{
	return ConvertToWebSocketProtocolString(InProtocol);
}

EWebSocketCode UBPFunctions_WebSocket::BP_ConvertToWebSocketCodeEnum(int32 InCode)
{
	return ConvertToWebSocketCodeEnum(InCode);
}

int32 UBPFunctions_WebSocket::BP_ConvertToWebSocketCodeInt(EWebSocketCode InCode)
{
	return ConvertToWebSocketCodeInt(InCode);
}

FString UBPFunctions_WebSocket::GetWebSocketUrl(FString Host, int32 Port, EWebSocketProtocol Protocol)
{
	FStringFormatNamedArguments Arguments;
	Arguments.Add(TEXT("PROTOCOL"), ConvertToWebSocketProtocolString(Protocol));
	Arguments.Add(TEXT("Address"), UBPFunctions_Protocol::GetAddress(Host, Port));

	return FString::Format(TEXT("{PROTOCOL}://{Address}"), Arguments);
}
