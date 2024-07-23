// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandlePossessPawn.h"

#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"

void UCBE_HandlePossessPawn::NativeOnActived()
{
	Super::NativeOnActived();

	for (const auto& ActivePawnTag : ActivePawnTags)
	{
		GetManager<UPawnManager>()->PossessPawn(ActivePawnTag.Key, ActivePawnTag.Value);
	}
}

void UCBE_HandlePossessPawn::NativeOnInactived()
{
	Super::NativeOnInactived();


	for (const auto& InactivePawnTag : InactivePawnTags)
	{
		GetManager<UPawnManager>()->PossessPawn(InactivePawnTag.Key, InactivePawnTag.Value);
	}
}
