// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Camera.generated.h"

class UCameraComponent;
class UGenericCameraSwitchMethod;
class ACameraPointBase;

/**
 * 
 */
UCLASS()
class GENERICCAMERASYSTEM_API UBPFunctions_Camera : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"))
	static ACameraPointBase* GetCameraPoint(const UObject* WorldContextObject, FGameplayTag InCameraTag);

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByTransform(Class)")
	static void SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByTransform")
	static void SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByActor(Class)")
	static void SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByActor")
	static void SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByComponent(Class)")
	static void SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByComponent")
	static void SwitchToCamera_Component_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName = "SwitchToCameraByTag(Class)")
	static void SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, FGameplayTag InCameraTag, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName = "SwitchToCameraByTag")
	static void SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByCameraPoint(Class)")
	static void SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCameraByCameraPoint")
	static void SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCurrentCamera(Class)")
	static void SwitchToCurrent_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToCurrentCamera")
	static void SwitchToCurrent_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToPreviousCamera(Class)")
	static void SwitchToPrevious_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName = "SwitchToPreviousCamera")
	static void SwitchToPrevious_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle);
};
