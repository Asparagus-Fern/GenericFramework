// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Camera.generated.h"

class UCameraComponent;
class UCameraSwitchMethod;
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
	static void SwitchToCamera_Transform_HandleClass(int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByTransform")
	static void SwitchToCamera_Transform_Handle(int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByActor(Class)")
	static void SwitchToCamera_Actor_HandleClass(int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByActor")
	static void SwitchToCamera_Actor_Handle(int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByComponent(Class)")
	static void SwitchToCamera_Component_HandleClass(int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName="SwitchToCameraByComponent")
	static void SwitchToCamera_Component_Handle(int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="Camera"), DisplayName = "SwitchToCameraByTag(Class)")
	static void SwitchToCamera_Tag_HandleClass(int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="Camera"), DisplayName ="SwitchToCameraByTag")
	static void SwitchToCamera_Tag_Handle(int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCameraByCameraPoint(Class)")
	static void SwitchToCamera_CameraPoint_HandleClass(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCameraByCameraPoint")
	static void SwitchToCamera_CameraPoint_Handle(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCurrentCamera(Class)")
	static void SwitchToCurrent_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToCurrentCamera")
	static void SwitchToCurrent_Handle(int32 InPlayerIndex, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToPreviousCamera(Class)")
	static void SwitchToPrevious_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, DisplayName ="SwitchToPreviousCamera")
	static void SwitchToPrevious_Handle(int32 InPlayerIndex, UCameraSwitchMethod* InCameraHandle);
};
