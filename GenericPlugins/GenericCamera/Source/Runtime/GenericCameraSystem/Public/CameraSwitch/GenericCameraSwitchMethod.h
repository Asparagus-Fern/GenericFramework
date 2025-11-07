// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Obect/GenericObject.h"
#include "GenericCameraSwitchMethod.generated.h"

class UGenericCameraSwitchMethod;
class UCameraComponent;
class ACameraPointBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FCameraHandleDelegate, UGenericCameraSwitchMethod*)

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, MinimalAPI)
class UGenericCameraSwitchMethod : public UGenericObject
{
	GENERATED_BODY()

public:
	/* 处理相机过渡 */
	UFUNCTION(BlueprintNativeEvent)
	GENERICCAMERASYSTEM_API bool HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint);
	GENERICCAMERASYSTEM_API virtual bool NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish = FSimpleDelegate());

	/* 当相机过渡被打断时 */
	UFUNCTION(BlueprintNativeEvent)
	GENERICCAMERASYSTEM_API void OnSwitchToCameraPointReset();
	GENERICCAMERASYSTEM_API virtual void NativeOnSwitchToCameraPointReset();

	/* 当相机过渡完成时 */
	UFUNCTION(BlueprintNativeEvent)
	GENERICCAMERASYSTEM_API void OnSwitchToCameraPointFinish();
	GENERICCAMERASYSTEM_API virtual void NativeOnSwitchToCameraPointFinish();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	GENERICCAMERASYSTEM_API float GetSwitchDuration();

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> OwnerPlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraPointBase> TargetCameraPoint = nullptr;

public:
	GENERICCAMERASYSTEM_API inline static FCameraHandleDelegate OnSwitchCameraBegin;
	GENERICCAMERASYSTEM_API inline static FCameraHandleDelegate OnSwitchCameraFinish;

protected:
	FSimpleDelegate OnHandleFinish;
};
