// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Scene.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Scene : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static bool IsPartitionedWorld(const UObject* WorldContextObject);
};
