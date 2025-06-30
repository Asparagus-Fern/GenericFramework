// Copyright ChenTaiye 2025. All Rights Reserved.


#include "TeamAssignPolicy.h"

#include "Gameplay/TeamPlayerState.h"

void UTeamAssignPolicy::InitAssignPolicy()
{
	if (TeamAssignMethod == ETeamAssignMethod::Static)
	{
		for (int32 i = 0; i < TeamCount; ++i)
		{
			PlayerTeams.Add(CreateNewTeam());
		}
	}
	else if (TeamAssignMethod == ETeamAssignMethod::Dynamic)
	{
		PlayerTeams.Add(CreateNewTeam());
	}
}

void UTeamAssignPolicy::LoginPlayer(ATeamPlayerState* InPlayerState)
{
	if (!IsValid(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (HasPlayer(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("InPlayerState Is Already In Team"))
		return;
	}

	PlayerStates.Add(InPlayerState);

	if (CanCreateNewTeam())
	{
		PlayerTeams.Add(CreateNewTeam());
	}

	FPlayerTeam& Team = GetTeamPlayerJoin(InPlayerState);
	if (CanPlayerJoinTeam(Team))
	{
		Team.PlayerStates.Add(InPlayerState);
		OnTeamPlayerAddedEvent.Broadcast(InPlayerState);
	}

	if (IsTeamFull() && bAutoFinishAssignTeam)
	{
		FinishAssignTeam();
	}
}

void UTeamAssignPolicy::LogoutPlayer(ATeamPlayerState* InPlayerState)
{
	if (!IsValid(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (!HasPlayer(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("InPlayerState Is Not In Team"))
		return;
	}

	PlayerStates.Remove(InPlayerState);

	for (auto& PlayerTeam : PlayerTeams)
	{
		if (PlayerTeam.PlayerStates.Contains(InPlayerState))
		{
			PlayerTeam.PlayerStates.Remove(InPlayerState);
		}
	}

	OnTeamPlayerRemovedEvent.Broadcast(InPlayerState);
}

TArray<FPlayerTeam>& UTeamAssignPolicy::GetPlayerTeams()
{
	return PlayerTeams;
}

bool UTeamAssignPolicy::HasPlayer(APlayerState* InPlayerState) const
{
	return PlayerStates.Contains(InPlayerState);
}

bool UTeamAssignPolicy::CanCreateNewTeam()
{
	if (PlayerTeams.IsEmpty())
	{
		return true;
	}

	if (PlayerTeams.Num() < MaxTeamCount && PlayerTeams.Last().PlayerStates.Num() >= MaxTeamPlayerCount)
	{
		return true;
	}

	return false;
}

FPlayerTeam UTeamAssignPolicy::CreateNewTeam()
{
	return FPlayerTeam(PlayerTeams.IsEmpty() ? 0 : PlayerTeams.Last().TeamID + 1);;
}

bool UTeamAssignPolicy::CanPlayerJoinTeam(const FPlayerTeam& InTeam)
{
	return InTeam.IsValid() && InTeam.PlayerStates.Num() < MaxTeamPlayerCount;
}

FPlayerTeam& UTeamAssignPolicy::GetTeamPlayerJoin(ATeamPlayerState* InPlayerState)
{
	if (TeamAssignMethod == ETeamAssignMethod::Static)
	{
		for (auto& PlayerTeam : PlayerTeams)
		{
			if (PlayerTeam.PlayerStates.Num() < MaxTeamPlayerCount)
			{
				return PlayerTeam;
			}
		}
	}

	return PlayerTeams.Last();
}

bool UTeamAssignPolicy::IsTeamFull()
{
	if (PlayerTeams.Num() < MaxTeamCount)
	{
		return false;
	}

	for (auto& PlayerTeam : PlayerTeams)
	{
		if (PlayerTeam.PlayerStates.Num() < MaxTeamPlayerCount)
		{
			return false;
		}
	}

	return true;
}

void UTeamAssignPolicy::FinishAssignTeam()
{
	OnTeamAssignFinishEvent.Broadcast();
}
