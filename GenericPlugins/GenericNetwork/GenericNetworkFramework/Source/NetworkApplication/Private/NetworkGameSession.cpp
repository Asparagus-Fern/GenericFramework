// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "NetworkGameSession.h"

#include "GameFramework/PlayerState.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"

ANetworkGameSession::ANetworkGameSession()
{
}

// void ANetworkGameSession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite)
// {
// 	Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);
//
// 	FName a = SessionName;
// 	FName b = NewPlayer->GetPlayerState<APlayerState>()->SessionName;
//
// 	if (a == b)
// 	{
// 	}
// 	else
// 	{
// 	}
// }
