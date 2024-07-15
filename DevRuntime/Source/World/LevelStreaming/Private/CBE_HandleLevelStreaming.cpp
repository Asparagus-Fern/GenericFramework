// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleLevelStreaming::NativeOnCreate()
{
	Super::NativeOnCreate();

	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(VisibleLevelsOnCreated, true, FOnOnceFinish(), FOnFinish());
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(HiddenLevelsOnCreated, false, FOnOnceFinish(), FOnFinish());
}

void UCBE_HandleLevelStreaming::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(VisibleLevelsOnDestroy, true, FOnOnceFinish(), FOnFinish());
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(HiddenLevelsOnDestroy, false, FOnOnceFinish(), FOnFinish());
}

void UCBE_HandleLevelStreaming::NativeOnActived()
{
	Super::NativeOnActived();

	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnActivateVisibleLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(ActivateVisibleLevels, true, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::NativeOnInactived()
{
	Super::NativeOnInactived();

	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnInactivateVisibleLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(InactivateVisibleLevels, true, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::OnActivateVisibleLevelsFinish()
{
	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnActivateHiddenLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(ActivateHiddenLevels, false, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::OnActivateHiddenLevelsFinish()
{
	RequestActivateFinish();
}

void UCBE_HandleLevelStreaming::OnInactivateVisibleLevelsFinish()
{
	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UCBE_HandleLevelStreaming::OnInactivateHiddenLevelsFinish);
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(InactivateHiddenLevels, false, FOnOnceFinish(), OnFinish);
}

void UCBE_HandleLevelStreaming::OnInactivateHiddenLevelsFinish()
{
	RequestInactivateFinish();
}
