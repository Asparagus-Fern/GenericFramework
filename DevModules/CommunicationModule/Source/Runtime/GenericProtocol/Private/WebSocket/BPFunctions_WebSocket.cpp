// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/BPFunctions_WebSocket.h"

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
	Arguments.Add(TEXT("HOST"), Host);
	Arguments.Add(TEXT("PORT"), FString::FromInt(Port));

	return FString::Format(TEXT("{PROTOCOL}://{HOST:PORT}"), Arguments);
}
