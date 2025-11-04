// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoad.h"

#include "ProcedureFlowSubsystem.h"

void UProcedureFlowLoad::SwitchToNextProcedureFlow() const
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(this))
	{
		ProcedureFlowSubsystem->EnterProcedureFlow(NextProcedureFlowTag);
	}
}
