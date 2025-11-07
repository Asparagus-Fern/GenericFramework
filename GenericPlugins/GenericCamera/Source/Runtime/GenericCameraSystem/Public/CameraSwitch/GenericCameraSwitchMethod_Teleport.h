// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraSwitch/GenericCameraSwitchMethod.h"
#include "GenericCameraSwitchMethod_Teleport.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericCameraSwitchMethod_Teleport : public UGenericCameraSwitchMethod
{
	GENERATED_BODY()

public:
	GENERICCAMERASYSTEM_API virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	GENERICCAMERASYSTEM_API virtual void OnSwitchToCameraPointFinish_Implementation() override;

protected:
	bool bUpdatePawnCenterPointAfterSwitchFinish = false;
};
