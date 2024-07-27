// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Camera.generated.h"

class UCameraComponent;
class UCameraHandle;
class ACameraPointBase;

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UBPFunctions_Camera : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Camera"))
	static ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Camera"))
	static bool CanSwitchToCamera(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Camera"))
	static void SwitchToCameraByComponentClass(UCameraComponent* InComponent, TSubclassOf<UCameraHandle> SwitchCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Camera"))
	static void SwitchToCameraByComponent(UCameraComponent* InComponent, UCameraHandle* SwitchCameraHandle);
	
	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Camera"))
	static void SwitchToCameraByHandleClass(FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> SwitchCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Camera"))
	static void SwitchToCameraByHandle(FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle);
};
