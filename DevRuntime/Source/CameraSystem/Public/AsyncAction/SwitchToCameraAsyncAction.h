// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SwitchToCameraAsyncAction.generated.h"

class ACameraPointBase;
class UCameraComponent;
class UCameraHandle;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCaneraHandleDelegate);

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API USwitchToCameraAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByTransform(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByTransform")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByActor(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByActor")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByComponent(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName="AsyncSwitchToCameraByComponent")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName = "AsyncSwitchToCameraByTag(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName ="AsyncSwitchToCameraByTag")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName ="AsyncSwitchToCameraByCameraPoint(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraHandle> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), DisplayName ="AsyncSwitchToCameraByCameraPoint")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* InCameraHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FCaneraHandleDelegate OnFinish;

protected:
	virtual void OnHandleFinish();
};
