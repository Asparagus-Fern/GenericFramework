// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "UObject/Object.h"
#include "CameraHandle.generated.h"

class ACameraPointBase;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bLockLocation : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bLockRotation : 1;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint);

public:
	UPROPERTY(BlueprintAssignable)
	FOnSwitchCameraFinish OnSwitchCameraFinish;

	UPROPERTY(BlueprintReadOnly)
	APlayerController* OwnerPlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACameraPointBase* TargetCameraPoint = nullptr;

protected:
	FDelegateHandle SwitchCameraPointHandle;
	virtual void OnSwitchToCameraPointFinish();
};
