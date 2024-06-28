#include "Procedure/ProcedureType.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Procedure, "Procedure");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureLoading, "Procedure.Loading");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureMainMenu, "Procedure.MainMenu");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePlay, "Procedure.Play");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePause, "Procedure.Pause");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureExit, "Procedure.Exit");

FProcedureInterfaceHandle::FProcedureInterfaceHandle()
	: Interface(nullptr),
	  bTargetActiveState(false)
{
}

FProcedureInterfaceHandle::FProcedureInterfaceHandle(IProcedureInterface* InInterface, bool InTargetActiveState)
	: Interface(InInterface),
	  bTargetActiveState(InTargetActiveState)
{
}
