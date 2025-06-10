// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_Protocol.h"

FString UBPFunctions_Protocol::GetAddress(FString Host, int32 Port)
{
	FStringFormatNamedArguments Arguments;
	Arguments.Add(TEXT("HOST"), Host);
	Arguments.Add(TEXT("PORT"), FString::FromInt(Port));

	return FString::Format(TEXT("{HOST}:{PORT}"), Arguments);
}
