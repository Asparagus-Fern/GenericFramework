// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleLevelStreaming::NativeOnActived()
{
	Super::NativeOnActived();
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(HandleLevels, bLevelVisibility, FOnOnceFinish(), FOnFinish());
}

void UCBE_HandleLevelStreaming::NativeOnInactived()
{
	Super::NativeOnInactived();
	GetManager<ULevelStreamingManager>()->SetLevelsVisibility(HandleLevels, bLevelVisibility, FOnOnceFinish(), FOnFinish());
}
