// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "UObject/Object.h"
#include "CameraHandle.generated.h"

class ACameraPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchCameraFinish);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CAMERASYSTEM_API UCameraHandle : public UObject
{
	GENERATED_BODY()

public:
	UCameraHandle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bLockCamera : 1;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPoint* InCameraPoint);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSwitchToCameraPointFinish();

public:
	UPROPERTY(BlueprintAssignable)
	FOnSwitchCameraFinish OnSwitchCameraFinish;

	UPROPERTY(BlueprintReadOnly)
	APlayerController* OwnerPlayerController = nullptr;

protected:
	FDelegateHandle SwitchCameraPointHandle;
};
