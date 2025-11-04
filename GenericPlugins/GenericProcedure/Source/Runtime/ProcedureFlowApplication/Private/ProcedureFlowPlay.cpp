// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowPlay.h"

#include "GenericCameraSubsystem.h"
#include "CameraSwitch/GenericCameraSwitchMethod.h"

void UProcedureFlowPlay::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (UGenericCameraSubsystem* CameraManager = UGenericCameraSubsystem::Get(this))
	{
		if (DefaultCameraTag.IsValid() && IsValid(CameraHandle))
		{
			if (CameraManager->CanSwitchToCamera(DefaultCameraTag))
			{
				CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
			}
		}
	}
}

void UProcedureFlowPlay::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}
