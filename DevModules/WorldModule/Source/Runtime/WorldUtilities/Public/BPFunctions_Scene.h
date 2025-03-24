// Copyright ChenTaiye 2025. All Rights Reserved.

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
	UFUNCTION(BlueprintPure)
	static float GetPlayerForwardAngle(int32 PlayerIndex = 0);

	/* 获取高度的格式化文本 */
	UFUNCTION(BlueprintPure)
	static FString GetUnrealUnitsFormatString(float UnrealUnits);
};
