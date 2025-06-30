// Copyright ChenTaiye 2025. All Rights Reserved.

#include "TeamState.h"

#include "Gameplay/TeamGameState.h"
#include "Gameplay/TeamPlayerState.h"
#include "Net/UnrealNetwork.h"

ATeamState::ATeamState()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

bool ATeamState::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (const APlayerController* TargetPC = Cast<APlayerController>(RealViewer))
	{
		if (const APlayerState* TargetPS = Cast<APlayerState>(TargetPC->PlayerState))
		{
			if (ATeamGameState* TeamGameState = Cast<ATeamGameState>(GetWorld()->GetGameState()))
			{
				const TArray<FPlayerTeam>& PlayerTeams = TeamGameState->GetPlayerTeams();

				const FPlayerTeam* PlayerTeam = PlayerTeams.FindByPredicate([this](const FPlayerTeam& PlayerTeam)
					{
						return PlayerTeam.TeamState == this;
					}
				);

				if (PlayerTeam)
				{
					return PlayerTeam->PlayerStates.Contains(TargetPS);
				}
			}
		}
	}

	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}
