// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Pawn.h"

#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"

void UBPFunctions_Pawn::PossessPawn(int32 PlayerIndex, const FGameplayTag InPawnTag)
{
	GetManager<UPawnManager>()->PossessPawn(PlayerIndex, InPawnTag);
}

APawn* UBPFunctions_Pawn::GetPawn(const FGameplayTag InPawnTag)
{
	return GetManager<UPawnManager>()->GetPawn(InPawnTag);
}
