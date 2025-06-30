// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Gameplay/TeamPlayerState.h"

#include "Gameplay/TeamGameState.h"
#include "Net/UnrealNetwork.h"

bool ATeamPlayerState::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (const APlayerController* TargetPC = Cast<APlayerController>(RealViewer))
	{
		if (const ATeamPlayerState* TargetPS = Cast<ATeamPlayerState>(TargetPC->PlayerState))
		{
			if (ATeamGameState* TeamGameState = Cast<ATeamGameState>(GetWorld()->GetGameState()))
			{
				const TArray<FPlayerTeam>& PlayerTeams = TeamGameState->GetPlayerTeams();

				const FPlayerTeam* PlayerTeam = PlayerTeams.FindByPredicate([this](const FPlayerTeam& PlayerTeam)
					{
						return PlayerTeam.PlayerStates.Contains(this);
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
