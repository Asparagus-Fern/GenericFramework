// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_Scene.h"

#include "SceneManager.h"

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

float UBPFunctions_Scene::GetPlayerPointToNorthAngle(const UObject* WorldContextObject, const int32 PlayerIndex)
{
	if (const USceneManager* SceneManager = GetManager<USceneManager>(WorldContextObject))
	{
		return SceneManager->GetPlayerPointToNorthAngle(PlayerIndex);
	}

	return 0.f;
}
