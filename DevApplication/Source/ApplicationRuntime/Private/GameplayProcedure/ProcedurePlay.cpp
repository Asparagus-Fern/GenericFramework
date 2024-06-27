// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedurePlay.h"

#include "ActiveNodeManager.h"
#include "ActiveNodeSubsystem.h"
#include "LevelStreamingManager.h"
#include "Manager/ManagerGlobal.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePlay_Default, "Procedure.Play.Default");

void UProcedurePlay::NativeOnActived()
{
	Super::NativeOnActived();


	// FOnFinish SetAlwaysVisibleLevelsDelegate;
	// SetAlwaysVisibleLevelsDelegate.BindUFunction(this, "OnSetAlwaysVisibleLevelsFinish");
	// GetManager<ULevelStreamingManager>()->SetLevelsVisibility(GetManager<ULevelStreamingManager>()->AlwaysLoadLevels, true, FOnOnceFinish(), SetAlwaysVisibleLevelsDelegate);
}

void UProcedurePlay::NativeOnInactived()
{
	Super::NativeOnInactived();
}

void UProcedurePlay::OnSetAlwaysVisibleLevelsFinish()
{
	// OnFinish_SetAlwaysVisibleLevels();
	// UActiveNodeSubsystem::ChangeActiveNodeTo(this, GetManager<UActiveNodeManager>()->DefaultNodeTag, false);
}

void UProcedurePlay::OnFinish_SetAlwaysVisibleLevels_Implementation()
{
}
