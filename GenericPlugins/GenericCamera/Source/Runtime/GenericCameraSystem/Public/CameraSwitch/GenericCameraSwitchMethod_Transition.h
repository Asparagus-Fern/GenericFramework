// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraSwitch/GenericCameraSwitchMethod.h"
#include "GenericCameraSwitchMethod_Transition.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericCameraSwitchMethod_Transition : public UGenericCameraSwitchMethod
{
	GENERATED_BODY()

public:
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod_Transition(const FObjectInitializer& ObjectInitializer);
	GENERICCAMERASYSTEM_API virtual bool HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint) override;
	GENERICCAMERASYSTEM_API virtual void OnSwitchToCameraPointFinish_Implementation() override;
	GENERICCAMERASYSTEM_API virtual float GetSwitchDuration_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FViewTargetTransitionParams ViewTargetTransitionParams;

protected:
	FTimerHandle TimerHandle;
};
