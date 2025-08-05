// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WebSocket/BPFunctions_WebSocket.h"

EGenericWebSocketProtocol UBPFunctions_WebSocket::BP_ConvertToWebSocketProtocolEnum(FString InProtocol)
{
	return ConvertToWebSocketProtocolEnum(InProtocol);
}

FString UBPFunctions_WebSocket::BP_ConvertToWebSocketProtocolString(EGenericWebSocketProtocol InProtocol)
{
	return ConvertToWebSocketProtocolString(InProtocol);
}

EGenericWebSocketCode UBPFunctions_WebSocket::BP_ConvertToWebSocketCodeEnum(int32 InCode)
{
	return ConvertToWebSocketCodeEnum(InCode);
}

int32 UBPFunctions_WebSocket::BP_ConvertToWebSocketCodeInt(EGenericWebSocketCode InCode)
{
	return ConvertToWebSocketCodeInt(InCode);
}

FString UBPFunctions_WebSocket::GetWebSocketUrl(FString Host, int32 Port, EGenericWebSocketProtocol Protocol)
{
	FStringFormatNamedArguments Arguments;
	Arguments.Add(TEXT("PROTOCOL"), ConvertToWebSocketProtocolString(Protocol));
	Arguments.Add(TEXT("HOST"), Host);
	Arguments.Add(TEXT("PORT"), FString::FromInt(Port));

	return FString::Format(TEXT("{PROTOCOL}://{HOST:PORT}"), Arguments);
}
