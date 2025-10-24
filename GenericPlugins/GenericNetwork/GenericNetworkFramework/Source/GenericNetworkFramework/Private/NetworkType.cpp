// Copyright ChenTaiye 2025. All Rights Reserved.


#include "NetworkType.h"

#include "BPFunctions/BPFunctions_Device.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY(GenericLogNetwork);

FUniqueNetworkID::FUniqueNetworkID()
{
	UniqueID = UBPFunctions_Device::GetDeviceID();
}

FUniqueNetworkID::FUniqueNetworkID(const ULocalPlayer* InLocalPlayer)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();

	if (IsValid(InLocalPlayer))
	{
		UniqueIdRepl = InLocalPlayer->GetPreferredUniqueNetId();
	}
}

FUniqueNetworkID::FUniqueNetworkID(const APlayerController* InPlayer)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();

	if (IsValid(InPlayer))
	{
		if (APlayerState* PlayerState = InPlayer->GetPlayerState<APlayerState>())
		{
			UniqueIdRepl = PlayerState->GetUniqueId();
		}
	}
}

FUniqueNetworkID::FUniqueNetworkID(const APlayerState* InPlayerState)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();

	if (IsValid(InPlayerState))
	{
		UniqueIdRepl = InPlayerState->GetUniqueId();
	}
}
