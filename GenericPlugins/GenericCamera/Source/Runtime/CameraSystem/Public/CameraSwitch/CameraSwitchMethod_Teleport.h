// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "CameraSwitchMethod_Teleport.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraSwitchMethod_Teleport : public UCameraSwitchMethod
{
	GENERATED_BODY()

public:
	CAMERASYSTEM_API virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	CAMERASYSTEM_API virtual void OnSwitchToCameraPointFinish_Implementation() override;

protected:
	bool bUpdatePawnCenterPointAfterSwitchFinish = false;
};
