// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoad.h"

#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

void UProcedureFlowLoad::SwitchToNextProcedureFlow() const
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(NextProcedureFlowTag);
	}
}
