// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Gameplay/TeamAllocationGameState.h"

#include "Gameplay/TeamAllocationPlayerController.h"
#include "Net/UnrealNetwork.h"

void ATeamAllocationGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
	}
	else
	{
	}
}

void ATeamAllocationGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATeamAllocationGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ATeamAllocationGameState, TeamAllocationPanelClass, SharedParams);
}

void ATeamAllocationGameState::OnRep_TeamAllocationPanelClass()
{
	if (!HasAuthority())
	{
		if (ATeamAllocationPlayerController* PC = GetWorld()->GetFirstPlayerController<ATeamAllocationPlayerController>())
		{
		}
	}
}
