// Copyright ChenTaiye 2025. All Rights Reserved.


#include "TeamType.h"

FPlayerTeam::FPlayerTeam()
{
}

FPlayerTeam::FPlayerTeam(int32 InTeamID)
	: TeamID(InTeamID)
{
}

FPlayerTeam::FPlayerTeam(ATeamPlayerState* InPlayerState)
{
	PlayerStates.Add(InPlayerState);
}

FPlayerTeam::FPlayerTeam(int32 InTeamID, ATeamPlayerState* InPlayerState)
	: TeamID(InTeamID)
{
	PlayerStates.Add(InPlayerState);
}
