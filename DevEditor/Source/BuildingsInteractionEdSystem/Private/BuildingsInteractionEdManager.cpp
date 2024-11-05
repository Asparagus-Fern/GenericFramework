// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsInteractionEdManager.h"

#include "BPFunctions/BPFunctions_EditorScene.h"
#include "Floor/FloorBodyComponent.h"

void UBuildingsInteractionEdManager::NativeOnCreate()
{
	Super::NativeOnCreate();
}

void UBuildingsInteractionEdManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();
}

void UBuildingsInteractionEdManager::OnFloorBodyRefresh(UFloorBodyComponent* InFloorBodyComponent)
{
	UBPFunctions_EditorScene::RefreshSelection();
}
