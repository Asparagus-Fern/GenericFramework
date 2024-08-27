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
	UFUNCTION(BlueprintPure, meta=( GameplayTagFilter="Camera"))
	static ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag);

public:
	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByTransform(Class)")
	static void SwitchToCamera_Transform_HandleClass(int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByTransform")
	static void SwitchToCamera_Transform_Handle(int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByActor(Class)")
	static void SwitchToCamera_Actor_HandleClass(int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByActor")
	static void SwitchToCamera_Actor_Handle(int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByComponent(Class)")
	static void SwitchToCamera_Component_HandleClass(int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByComponent")
	static void SwitchToCamera_Component_Handle(int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="Camera"), DisplayName = "SwitchToCameraByTag(Class)")
	static void SwitchToCamera_Tag_HandleClass(int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="Camera"), DisplayName ="SwitchToCameraByTag")
	static void SwitchToCamera_Tag_Handle(int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCameraByCameraPoint(Class)")
	static void SwitchToCamera_CameraPoint_HandleClass(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCameraByCameraPoint")
	static void SwitchToCamera_CameraPoint_Handle(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* InCameraHandle);
};
