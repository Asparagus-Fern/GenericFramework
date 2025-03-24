// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "CameraHandle_Teleport.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraHandle_Teleport : public UCameraSwitchMethod
{
	GENERATED_BODY()

public:
	UCameraHandle_Teleport();
	virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	virtual void OnSwitchToCameraPointFinish_Implementation() override;

protected:
	bool bUpdatePawnCenterPointAfterSwitchFinish = false;
};
