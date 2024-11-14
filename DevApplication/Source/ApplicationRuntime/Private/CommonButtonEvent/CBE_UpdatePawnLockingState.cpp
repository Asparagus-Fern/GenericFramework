// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_UpdatePawnLockingState.h"

#include "Kismet/GameplayStatics.h"
#include "Pawn/DevPawn.h"
#include "Pawn/PawnManager.h"

bool UCBE_UpdatePawnLockingState::CanExecuteButtonEvent_Implementation()
{
	bool IsValidPlayer = false;
	if (const UPawnManager* PawnManager = GetManager<UPawnManager>())
	{
		IsValidPlayer = IsValid(UGameplayStatics::GetPlayerController(PawnManager, TargetPlayerIndex));
	}

	return IsValidPlayer;
}

void UCBE_UpdatePawnLockingState::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (const UPawnManager* PawnManager = GetManager<UPawnManager>())
	{
		if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(PawnManager, TargetPlayerIndex))
		{
			if (Pawn->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
			{
				IPawnLockStateInterface::Execute_SetPawnLockState(Pawn, PawnLockingState);
			}
		}
	}

	if (bIsAsync)
		MarkAsActivedFinish();
}
