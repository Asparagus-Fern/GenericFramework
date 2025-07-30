// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "CameraSwitchMethod.generated.h"

class UCameraComponent;
class ACameraPointBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchCameraFinish);

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, MinimalAPI)
class UCameraSwitchMethod : public UGenericObject
{
	GENERATED_BODY()

public:
	CAMERASYSTEM_API virtual UWorld* GetWorld() const override;

public:
	UFUNCTION(BlueprintCallable)
	CAMERASYSTEM_API void Reset();

public:
	/* 处理相机过渡 */
	UFUNCTION(BlueprintNativeEvent)
	CAMERASYSTEM_API bool HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint);
	CAMERASYSTEM_API virtual bool NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish = FSimpleDelegate());

	/* 当相机过渡被打断时 */
	UFUNCTION(BlueprintNativeEvent)
	CAMERASYSTEM_API void OnSwitchToCameraPointReset();
	CAMERASYSTEM_API virtual void NativeOnSwitchToCameraPointReset();

	/* 当相机过渡完成时 */
	UFUNCTION(BlueprintNativeEvent)
	CAMERASYSTEM_API void OnSwitchToCameraPointFinish();
	CAMERASYSTEM_API virtual void NativeOnSwitchToCameraPointFinish();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	CAMERASYSTEM_API float GetSwitchDuration();

public:
	UPROPERTY(BlueprintReadOnly)
	APlayerController* OwnerPlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACameraPointBase* TargetCameraPoint = nullptr;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraHandleDelegate, UCameraSwitchMethod*)
	CAMERASYSTEM_API inline static FCameraHandleDelegate OnSwitchCameraBegin;
	CAMERASYSTEM_API inline static FCameraHandleDelegate OnSwitchCameraFinish;

protected:
	FSimpleDelegate OnHandleFinish;
};
