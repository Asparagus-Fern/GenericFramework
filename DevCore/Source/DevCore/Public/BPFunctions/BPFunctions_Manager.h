// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Manager.generated.h"

class UManagerInfo;
class UManagerProxy;

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Manager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Function Library | Manager")
	static UManagerProxy* GetManagerProxy();

	UFUNCTION(BlueprintPure, Category="Function Library | Manager")
	static UManagerInfo* GetManagerInfo(FName InManagerName);

	UFUNCTION(BlueprintPure, Category="Function Library | Manager")
	static TArray<UManagerInfo*> GetManagerInfos();
};
