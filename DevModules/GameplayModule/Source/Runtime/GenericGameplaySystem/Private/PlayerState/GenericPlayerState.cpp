// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerState/GenericPlayerState.h"

int32 AGenericPlayerState::GetPlayerIdentity()
{
	return GetPlayerId();
}

const FUniqueNetIdRepl& AGenericPlayerState::GetPlayerUniqueIdentity()
{
	return GetUniqueId();
}
