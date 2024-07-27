// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "Object/CommonObject.h"
#include "CameraHandle.generated.h"

class UCameraComponent;
class ACameraPointBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchCameraFinish);

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class CAMERASYSTEM_API UCameraHandle : public UCommonObject
{
	GENERATED_BODY()

public:
	UCameraHandle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bLock : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bLock"))
	uint8 bLockLocation : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bLock"))
	uint8 bLockRotation : 1;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSwitchToCameraPointFinish();

public:
	UPROPERTY(BlueprintReadOnly)
	APlayerController* OwnerPlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACameraPointBase* TargetCameraPoint = nullptr;

protected:
	void NativeOnSwitchToCameraPointFinish();
};
