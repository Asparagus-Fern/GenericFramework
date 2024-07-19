// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraHandle.h"
#include "CameraHandle_Default.generated.h"

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UCameraHandle_Default : public UCameraHandle
{
	GENERATED_BODY()

public:
	UCameraHandle_Default();
	virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	virtual void OnSwitchToCameraPointFinish() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FViewTargetTransitionParams ViewTargetTransitionParams;

protected:
	FTimerHandle TimerHandle;
};
