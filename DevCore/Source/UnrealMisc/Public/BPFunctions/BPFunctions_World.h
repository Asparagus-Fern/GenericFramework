// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Type/WorldType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_World.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_World : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsPartitionedWorld(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static EWorldTypeBP GetWorldType(const UObject* WorldContextObject);

public:
	/* 获取高度的格式化文本 */
	// UFUNCTION(BlueprintPure)
	// static FString GetUnrealUnitsFormatString(float UnrealUnits);
};
