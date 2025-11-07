// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SwitchToCameraAsyncAction.generated.h"

class ACameraPointBase;
class UCameraComponent;
class UGenericCameraSwitchMethod;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraHandleFinish);

/**
 * 
 */
UCLASS()
class GENERICCAMERASYSTEM_API USwitchToCameraAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByTransform(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByTransform")
	static USwitchToCameraAsyncAction* SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByActor(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByActor")
	static USwitchToCameraAsyncAction* SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByComponent(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName="AsyncSwitchToCameraByComponent")
	static USwitchToCameraAsyncAction* SwitchToCamera_Component_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName = "AsyncSwitchToCameraByTag(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, FGameplayTag InCameraTag, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Camera"), DisplayName ="AsyncSwitchToCameraByTag")
	static USwitchToCameraAsyncAction* SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="AsyncSwitchToCameraByCameraPoint(Class)")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="AsyncSwitchToCameraByCameraPoint")
	static USwitchToCameraAsyncAction* SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="SwitchToCurrentCamera(Class)")
	static USwitchToCameraAsyncAction* SwitchToCurrent_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="SwitchToCurrentCamera")
	static USwitchToCameraAsyncAction* SwitchToCurrent_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="SwitchToPreviousCamera(Class)")
	static USwitchToCameraAsyncAction* SwitchToPrevious_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", BlueprintInternalUseOnly="true"), DisplayName ="SwitchToPreviousCamera")
	static USwitchToCameraAsyncAction* SwitchToPrevious_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FOnCameraHandleFinish OnFinish;

protected:
	virtual void OnHandleFinish();
};
