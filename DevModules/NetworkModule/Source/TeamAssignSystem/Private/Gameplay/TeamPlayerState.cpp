// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Gameplay/TeamPlayerState.h"

#include "TeamAssignComponent.h"

ATeamPlayerState::ATeamPlayerState()
{
	TeamAssignComponent = CreateDefaultSubobject<UTeamAssignComponent>(TEXT("TeamAssignComponent"));
}

bool ATeamPlayerState::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
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
