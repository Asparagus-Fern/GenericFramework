// Copyright ChenTaiye 2025. All Rights Reserved.

#include "TeamState.h"

#include "TeamAssignComponent.h"
#include "Gameplay/TeamGameState.h"
#include "Gameplay/TeamPlayerState.h"
#include "Net/UnrealNetwork.h"

ATeamState::ATeamState()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	TeamAssignComponent = CreateDefaultSubobject<UTeamAssignComponent>(TEXT("TeamAssignComponent"));
}

bool ATeamState::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (TeamAssignComponent->TeamID != INDEX_NONE)
	{
		if (UTeamAssignComponent* TargetTeamComponent = RealViewer->GetComponentByClass<UTeamAssignComponent>())
		{
			return TargetTeamComponent->TeamID == TeamAssignComponent->TeamID;
		}

		if (UTeamAssignComponent* TargetTeamComponent = ViewTarget->GetComponentByClass<UTeamAssignComponent>())
		{
			return TargetTeamComponent->TeamID == TeamAssignComponent->TeamID;
		}
	}

	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}
