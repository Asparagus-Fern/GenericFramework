// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedurePlay_Base.h"

#include "ActiveNodeManager.h"
#include "ActiveNodeSubsystem.h"
#include "World/WorldManager.h"

void UProcedurePlay_Base::NativeOnActived()
{
	Super::NativeOnActived();
	Execute_OnActived(this);

	/* todo:大世界游玩流程 */
	if (UWorldManager::Get()->bIsWorldPartition)
	{
	}
	/* 关卡流游玩流程 */
	else
	{
		FOnFinish SetAlwaysVisibleLevelsDelegate;
		SetAlwaysVisibleLevelsDelegate.BindUFunction(this, "OnSetAlwaysVisibleLevelsFinish");
		UWorldManager::Get()->SetLevelsVisibility(UWorldManager::Get()->AlwaysLoadLevels, true, FOnOnceFinish(), SetAlwaysVisibleLevelsDelegate);
	}
}

void UProcedurePlay_Base::NativeOnInactived()
{
	Super::NativeOnInactived();
	Execute_OnInactived(this);
}

void UProcedurePlay_Base::OnSetAlwaysVisibleLevelsFinish()
{
	OnFinish_SetAlwaysVisibleLevels();

	UActiveNodeSubsystem::ChangeActiveNodeTo(this, UActiveNodeManager::Get()->DefaultNodeTag, false);
}

void UProcedurePlay_Base::OnFinish_SetAlwaysVisibleLevels_Implementation()
{
}
