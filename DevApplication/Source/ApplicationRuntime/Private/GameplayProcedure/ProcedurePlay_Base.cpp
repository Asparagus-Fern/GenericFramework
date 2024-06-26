// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedurePlay_Base.h"

#include "ActiveNodeManager.h"
#include "ActiveNodeSubsystem.h"
#include "World/WorldManager.h"

void UProcedurePlay_Base::NativeOnActived()
{
	Super::NativeOnActived();
	Execute_OnActived(this);


	FOnFinish SetAlwaysVisibleLevelsDelegate;
	SetAlwaysVisibleLevelsDelegate.BindUFunction(this, "OnSetAlwaysVisibleLevelsFinish");
	GetManager<UWorldManager>()->SetLevelsVisibility(GetManager<UWorldManager>()->AlwaysLoadLevels, true, FOnOnceFinish(), SetAlwaysVisibleLevelsDelegate);
}

void UProcedurePlay_Base::NativeOnInactived()
{
	Super::NativeOnInactived();
	Execute_OnInactived(this);
}

void UProcedurePlay_Base::OnSetAlwaysVisibleLevelsFinish()
{
	OnFinish_SetAlwaysVisibleLevels();


	UActiveNodeSubsystem::ChangeActiveNodeTo(this, GetManager<UActiveNodeManager>()->DefaultNodeTag, false);
}

void UProcedurePlay_Base::OnFinish_SetAlwaysVisibleLevels_Implementation()
{
}
