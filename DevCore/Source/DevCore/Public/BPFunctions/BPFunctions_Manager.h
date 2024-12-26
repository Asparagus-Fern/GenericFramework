// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Manager.generated.h"

class AManagerActor;
class UManagerProxy;

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Manager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UManagerProxy* GetManagerProxy();

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"))
	static AManagerActor* GetManagerActorByClass(const TSubclassOf<AManagerActor> InClass);
};
