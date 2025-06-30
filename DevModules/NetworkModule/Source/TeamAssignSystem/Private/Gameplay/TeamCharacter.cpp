// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Gameplay/TeamCharacter.h"

#include "Gameplay/TeamGameState.h"
#include "Gameplay/TeamPlayerState.h"

ATeamCharacter::ATeamCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATeamCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATeamCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool ATeamCharacter::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
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
						return PlayerTeam.PlayerStates.Contains(GetPlayerState());
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
