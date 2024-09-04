// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Scene.h"

bool UBPFunctions_Scene::IsPartitionedWorld(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->IsPartitionedWorld();
	}

	return false;
}

ESceneWorldType UBPFunctions_Scene::GetWorldType(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return ConvertWorldTypeToSceneWorldType(World->WorldType);
	}

	return ESceneWorldType::None;
}
