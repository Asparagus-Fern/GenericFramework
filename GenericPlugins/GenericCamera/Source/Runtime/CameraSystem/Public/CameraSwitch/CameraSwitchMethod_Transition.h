// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "CameraSwitchMethod_Transition.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraSwitchMethod_Transition : public UCameraSwitchMethod
{
	GENERATED_BODY()

public:
	CAMERASYSTEM_API UCameraSwitchMethod_Transition(const FObjectInitializer& ObjectInitializer);
	CAMERASYSTEM_API virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	CAMERASYSTEM_API virtual void OnSwitchToCameraPointFinish_Implementation() override;
	CAMERASYSTEM_API virtual float GetSwitchDuration_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FViewTargetTransitionParams ViewTargetTransitionParams;

protected:
	FTimerHandle TimerHandle;
};
