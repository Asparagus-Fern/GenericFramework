// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunction_Network.h"

#include "GenericSessionSubsystem.h"

FUniqueNetworkID UBPFunction_Network::Conv_PlayerControllerToUniqueNetworkID(APlayerController* InPlayerController)
{
	return FUniqueNetworkID(InPlayerController);
}

FUniqueNetworkID UBPFunction_Network::Conv_PlayerStateToUniqueNetworkID(APlayerState* InPlayerState)
{
	return FUniqueNetworkID(InPlayerState);
}

FUniqueNetworkID UBPFunction_Network::Conv_UniqueNetIdReplToUniqueNetworkID(const FUniqueNetIdRepl& InUniqueNetIDRepl)
{
	return FUniqueNetworkID(InUniqueNetIDRepl);
}

bool UBPFunction_Network::GetSessionHandleByUniqueNetID(const UObject* WorldContextObject, const FUniqueNetworkID& UniqueNetworkID, FGenericSessionHandle& OutHandle)
{
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		return GenericSessionSubsystem->GetSessionHandle(UniqueNetworkID, OutHandle);
	}
	return false;
}

bool UBPFunction_Network::GetSessionHandleByNetID(const UObject* WorldContextObject, const FUniqueNetIdRepl& UniqueNetIDRepl, FGenericSessionHandle& OutHandle)
{
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		return GenericSessionSubsystem->GetSessionHandle(UniqueNetIDRepl, OutHandle);
	}
	return false;
}

bool UBPFunction_Network::GetSessionHandleByName(const UObject* WorldContextObject, FName InSessionName, FGenericSessionHandle& OutHandle)
{
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		return GenericSessionSubsystem->GetSessionHandle(InSessionName, OutHandle);
	}
	return false;
}
