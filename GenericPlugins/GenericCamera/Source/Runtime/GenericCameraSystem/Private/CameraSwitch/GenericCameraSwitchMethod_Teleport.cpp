// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraSwitch/GenericCameraSwitchMethod_Teleport.h"

bool UGenericCameraSwitchMethod_Teleport::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		NativeOnSwitchToCameraPointFinish();
		return true;
	}

	return false;
}

void UGenericCameraSwitchMethod_Teleport::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();
}
