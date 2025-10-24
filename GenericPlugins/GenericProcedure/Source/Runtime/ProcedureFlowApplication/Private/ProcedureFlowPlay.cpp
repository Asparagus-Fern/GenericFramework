// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowPlay.h"

#include "CameraManager.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "Manager/ManagerStatics.h"

void UProcedureFlowPlay::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (UCameraManager* CameraManager = GetManagerOwner<UCameraManager>())
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
