// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraHandle/CameraHandle.h"
#include "CameraHandle_Transition.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraHandle_Transition : public UCameraHandle
{
	GENERATED_BODY()

public:
	UCameraHandle_Transition();
	virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	virtual void OnSwitchToCameraPointFinish_Implementation() override;
	virtual float GetSwitchDuration_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FViewTargetTransitionParams ViewTargetTransitionParams;

protected:
	FTimerHandle TimerHandle;
};
