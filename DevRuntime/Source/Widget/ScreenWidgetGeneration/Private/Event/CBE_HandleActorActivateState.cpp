// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleActorActivateState.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UCBE_HandleActorActivateState::NativeOnActived()
{
	Super::NativeOnActived();

	for (const auto& ActiveHandleActor : ActiveHandleActorState)
	{
		GetManager<UProcedureManager>()->SetActorActivateState(ActiveHandleActor.Key, ActiveHandleActor.Value);
	}
}

void UCBE_HandleActorActivateState::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (const auto& ActiveHandleActor : InactiveHandleActorState)
	{
		GetManager<UProcedureManager>()->SetActorActivateState(ActiveHandleActor.Key, ActiveHandleActor.Value);
	}
}
