// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_Game.h"

#include "World/GameWorldSetting.h"
#include "World/LevelStreamingType.h"
#include "World/WorldManager.h"

AActiveNode_Game::AActiveNode_Game()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveNode_Game::LoginNode_Implementation()
{
	if (UWorldManager::Get()->bIsWorldPartition)
	{
	}
	else
	{
		/* 加载所有流关卡 */
		FOnFinish LoadCurrentWorldLevelStreamingDelegate;
		LoadCurrentWorldLevelStreamingDelegate.BindUFunction(this, "OnLoadCurrentWorldLevelStreamingFinish");
		UWorldManager::Get()->LoadCurrentWorldLevelStreaming(FOnOnceFinish(), LoadCurrentWorldLevelStreamingDelegate);
	}
}

void AActiveNode_Game::LogoutNode_Implementation()
{
}

void AActiveNode_Game::OnLoadCurrentWorldLevelStreamingFinish()
{
	if (IsValid(GameWorldSetting))
	{
		/* 设置默认显示项目关卡 */
		FOnFinish SetProjectLevelsVisibleDelegate;
		SetProjectLevelsVisibleDelegate.BindUFunction(this, "OnSetProjectLevelsVisibleFinish");
		UWorldManager::Get()->SetLevelsVisibility(GameWorldSetting->Levels, true, FOnOnceFinish(), SetProjectLevelsVisibleDelegate);
	}
	else
	{
		OnSetProjectLevelsVisibleFinish();
	}
}

void AActiveNode_Game::OnSetProjectLevelsVisibleFinish()
{
	OnFinish_SetProjectLevelsVisible();
}

void AActiveNode_Game::OnFinish_LoadCurrentWorldLevelStreaming_Implementation()
{
}

void AActiveNode_Game::OnFinish_SetProjectLevelsVisible_Implementation()
{
}
