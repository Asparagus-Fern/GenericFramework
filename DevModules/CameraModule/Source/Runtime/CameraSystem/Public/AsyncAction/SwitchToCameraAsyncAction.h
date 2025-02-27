// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SwitchToCameraAsyncAction.generated.h"

class ACameraPointBase;
class UCameraComponent;
class UCameraSwitchMethod;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCameraHandleDelegate);

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API USwitchToCameraAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByTransform(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_HandleClass(int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByTransform")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_Handle(int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByActor(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_HandleClass(int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByActor")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_Handle(int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByComponent(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_HandleClass(int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByComponent")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_Handle(int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName = "AsyncSwitchToCameraByTag(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_HandleClass(int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName ="AsyncSwitchToCameraByTag")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_Handle(int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="AsyncSwitchToCameraByCameraPoint(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_HandleClass(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="AsyncSwitchToCameraByCameraPoint")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_Handle(int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="SwitchToCurrentCamera(Class)")
	static USwitchToCameraAsyncAction* SwitchToCurrent_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="SwitchToCurrentCamera")
	static USwitchToCameraAsyncAction* SwitchToCurrent_Handle(int32 InPlayerIndex, UCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="SwitchToPreviousCamera(Class)")
	static USwitchToCameraAsyncAction* SwitchToPrevious_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"), DisplayName ="SwitchToPreviousCamera")
	static USwitchToCameraAsyncAction* SwitchToPrevious_Handle(int32 InPlayerIndex, UCameraSwitchMethod* InCameraHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FCameraHandleDelegate OnFinish;

protected:
	virtual void OnHandleFinish();
};
