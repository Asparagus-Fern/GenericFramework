// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraHandle/CameraHandle.h"
#include "CameraHandle_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCameraHandle_Teleport : public UCameraHandle
{
	GENERATED_BODY()

public:
	UCameraHandle_Teleport();
	virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	virtual void OnSwitchToCameraPointFinish_Implementation() override;

protected:
	bool bUpdatePawnCenterPointAfterSwitchFinish = false;
};
