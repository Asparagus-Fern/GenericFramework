// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleLevelStreaming::NativeOnActived()
{
	Super::NativeOnActived();

	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnActivateLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(ActivateLevels, true, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::NativeOnInactived()
{
	Super::NativeOnInactived();

	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnInactivateLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(InactivateLevels, false, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::OnActivateLevelsFinish()
{
	RequestActivateFinish();
}

void UCBE_HandleLevelStreaming::OnInactivateLevelsFinish()
{
	RequestInactivateFinish();
}
