// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Scene.generated.h"

/**
 * 
 */
UCLASS()
class WORLDUTILITIES_API UBPFunctions_Scene : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static bool IsPartitionedWorld(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static ESceneWorldType GetWorldType(const UObject* WorldContextObject);

public:
	/* 获取Player当前朝向和指定北方向间的夹角 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static float GetPlayerPointToNorthAngle(const UObject* WorldContextObject, int32 PlayerIndex = 0);
};
