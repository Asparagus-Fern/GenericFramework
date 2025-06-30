// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Gameplay/TeamGameState.h"

#include "TeamAssignPolicy.h"
#include "Debug/DebugType.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay/TeamPlayerState.h"
#include "Net/UnrealNetwork.h"

void ATeamGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TeamAssignPolicy = NewObject<UTeamAssignPolicy>(this, TeamAssignPolicyClass);
		TeamAssignPolicy->InitAssignPolicy();
		TeamAssignPolicy->OnTeamAssignFinishEvent.AddUniqueDynamic(this, &ATeamGameState::OnTeamAssignFinish);
	}
}

void ATeamGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HasAuthority())
	{
		if (TeamAssignPolicy)
		{
			TeamAssignPolicy->OnTeamAssignFinishEvent.RemoveAll(this);
		}
	}
}

void ATeamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ATeamGameState, PlayerTeams, SharedParams);
}

const TArray<FPlayerTeam>& ATeamGameState::GetPlayerTeams()
{
	return PlayerTeams;
}

bool ATeamGameState::GetPlayerTeamByID(int32 InTeamID, FPlayerTeam& OutPlayerTeam)
{
	FPlayerTeam* PlayerTeam = PlayerTeams.FindByPredicate([InTeamID](const FPlayerTeam& PlayerTeam)
		{
			return PlayerTeam.TeamID == InTeamID;
		}
	);

	if (PlayerTeam)
	{
		OutPlayerTeam = *PlayerTeam;
		return true;
	}

	return false;
}

bool ATeamGameState::GetPlayerTeamByTeamState(ATeamState* InTeamState, FPlayerTeam& OutPlayerTeam)
{
	FPlayerTeam* PlayerTeam = PlayerTeams.FindByPredicate([InTeamState](const FPlayerTeam& PlayerTeam)
		{
			return PlayerTeam.TeamState == InTeamState;
		}
	);

	if (PlayerTeam)
	{
		OutPlayerTeam = *PlayerTeam;
		return true;
	}

	return false;
}

bool ATeamGameState::GetPlayerTeamByPlayerState(APlayerState* InPlayerState, FPlayerTeam& OutPlayerTeam)
{
	FPlayerTeam* PlayerTeam = PlayerTeams.FindByPredicate([InPlayerState](const FPlayerTeam& PlayerTeam)
		{
			return PlayerTeam.PlayerStates.Contains(InPlayerState);
		}
	);

	if (PlayerTeam)
	{
		OutPlayerTeam = *PlayerTeam;
		return true;
	}

	return false;
}

void ATeamGameState::Server_LoginPlayer_Implementation(APlayerState* InPlayerState)
{
	if (!IsValid(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (!TeamAssignPolicy)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("TeamAssignPolicy Is InValid"))
		return;
	}

	if (ATeamPlayerState* TeamPlayerState = Cast<ATeamPlayerState>(InPlayerState))
	{
		TeamAssignPolicy->LoginPlayer(TeamPlayerState);
	}
}

void ATeamGameState::Server_LogoutPlayer_Implementation(APlayerState* InPlayerState)
{
	if (!IsValid(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (!TeamAssignPolicy)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("TeamAssignPolicy Is InValid"))
		return;
	}

	if (ATeamPlayerState* TeamPlayerState = Cast<ATeamPlayerState>(InPlayerState))
	{
		TeamAssignPolicy->LogoutPlayer(TeamPlayerState);
	}
}

void ATeamGameState::OnTeamAssignFinish()
{
	if (TeamAssignPolicy)
	{
		PlayerTeams = TeamAssignPolicy->GetPlayerTeams();

		TeamAssignPolicy->OnTeamAssignFinishEvent.RemoveAll(this);
		TeamAssignPolicy->MarkAsGarbage();

		if (!TeamStateClass)
		{
			GenericLOG(GenericLogNetwork, Error, TEXT("TeamStateClass Is InValid"))
			return;
		}

		for (auto& PlayerTeam : PlayerTeams)
		{
			ATeamState* NewTeamState = GetWorld()->SpawnActor<ATeamState>(TeamStateClass);
			PlayerTeam.TeamState = NewTeamState;
		}

		for (auto& PlayerTeam : PlayerTeams)
		{
			if (PlayerTeam.TeamState)
			{
				PlayerTeam.TeamState->InitTeamState(PlayerTeam.TeamID);
			}
		}
	}
}
