#include "ProcedureFlowNext.h"

#include "ProcedureFlowSubsystem.h"

void UProcedureFlowNext::SwitchToNextProcedureFlow() const
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(this))
	{
		ProcedureFlowSubsystem->EnterProcedureFlow(NextProcedureFlowTag);
	}
}
