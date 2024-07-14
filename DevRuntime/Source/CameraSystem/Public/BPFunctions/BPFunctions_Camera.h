// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Camera.generated.h"

class ACameraPointBase;

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UBPFunctions_Camera : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void AddCameraPoint(FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint);

	UFUNCTION(BlueprintCallable)
	static void RemoveCameraPoint(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintPure)
	static ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintPure)
	static bool CanSwitchToCamera(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintCallable)
	static void SwitchToCamera(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintCallable)
	static void SwitchToCameraByPlayerController(FGameplayTag InCameraTag, APlayerController* PlayerController);
};
