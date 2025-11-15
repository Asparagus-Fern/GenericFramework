// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunction_Network.h"

FUniqueNetworkID UBPFunction_Network::Conv_PlayerControllerToUniqueNetworkID(APlayerController* InPlayerController)
{
	return FUniqueNetworkID(InPlayerController);
}

FUniqueNetworkID UBPFunction_Network::Conv_PlayerStateToUniqueNetworkID(APlayerState* InPlayerState)
{
	return FUniqueNetworkID(InPlayerState);
}
