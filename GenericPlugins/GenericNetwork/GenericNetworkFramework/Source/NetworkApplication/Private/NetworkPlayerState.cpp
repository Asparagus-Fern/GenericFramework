// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "NetworkPlayerState.h"

#include "GenericSessionSubsystem.h"
#include "Net/OnlineEngineInterface.h"

void ANetworkPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ANetworkPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ANetworkPlayerState::RegisterPlayerWithSession(bool bWasFromInvite)
{
	// Super::RegisterPlayerWithSession(bWasFromInvite);

	/* Update Session Name From GenericSessionSubsystem */
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(this))
	{
		FGenericSessionHandle SessionHandle;
		GenericSessionSubsystem->GetSessionHandle(GetUniqueId(), SessionHandle);

		if (SessionHandle.CheckIsValid())
		{
			SessionName = SessionHandle.SessionName;
		}
	}

	/* Register Player With Custom Session Name */
	if (GetNetMode() != NM_Standalone)
	{
		if (GetUniqueId().IsValid())
		{
			if (UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(), SessionName))
			{
				UOnlineEngineInterface::Get()->RegisterPlayer(GetWorld(), SessionName, GetUniqueId(), bWasFromInvite);
			}
		}
	}
}

void ANetworkPlayerState::UnregisterPlayerWithSession()
{
	// Super::UnregisterPlayerWithSession();

	if (GetNetMode() == NM_Client && GetUniqueId().IsValid())
	{
		if (SessionName != NAME_None)
		{
			if (UOnlineEngineInterface::Get()->DoesSessionExist(GetWorld(), SessionName))
			{
				UOnlineEngineInterface::Get()->UnregisterPlayer(GetWorld(), SessionName, GetUniqueId());
			}
		}
	}
}
