// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Gameplay/TeamCharacter.h"

#include "TeamAssignComponent.h"
#include "Debug/DebugType.h"

ATeamCharacter::ATeamCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamAssignComponent = CreateDefaultSubobject<UTeamAssignComponent>(TEXT("TeamAssignComponent"));
}

bool ATeamCharacter::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	bool Result = Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);

	if (TeamAssignComponent->TeamID != INDEX_NONE)
	{
		if (UTeamAssignComponent* TargetTeamComponent = RealViewer->GetComponentByClass<UTeamAssignComponent>())
		{
			return Result && TargetTeamComponent->TeamID == TeamAssignComponent->TeamID;
		}

		if (UTeamAssignComponent* TargetTeamComponent = ViewTarget->GetComponentByClass<UTeamAssignComponent>())
		{
			return Result && TargetTeamComponent->TeamID == TeamAssignComponent->TeamID;
		}
	}

	return Result;
}
