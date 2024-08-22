#include "Procedure/ProcedureType.h"

#include "Procedure/ProcedureObject.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Procedure, "Procedure");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureLoading, "Procedure.Loading");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureMainMenu, "Procedure.MainMenu");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePlay, "Procedure.Play");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePause, "Procedure.Pause");
UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureExit, "Procedure.Exit");

FProcedureDelegates::FPocedureProxyDelegate FProcedureDelegates::OnProxyHandleBegin;
FProcedureDelegates::FPocedureProxyDelegate FProcedureDelegates::OnProxyHandlePause;
FProcedureDelegates::FPocedureProxyDelegate FProcedureDelegates::OnProxyHandleContinue;
FProcedureDelegates::FPocedureProxyDelegate FProcedureDelegates::OnProxyHandleStop;
FProcedureDelegates::FPocedureProxyDelegate FProcedureDelegates::OnProxyHandleFinish;
FProcedureDelegates::FOnGameplayProcedureSwitch FProcedureDelegates::OnGameplayProcedureSwitch;

FProcedureHandle::FProcedureHandle()
	: ProcedureObject(nullptr),
	  bTargetActiveState(false)
{
}

FProcedureHandle::FProcedureHandle(UProcedureObject* InProcedureObject, const bool InTargetActiveState, const bool InIsAsync)
	: ProcedureObject(InProcedureObject),
	  bTargetActiveState(InTargetActiveState)
{
}

FProcedureHandleGroup::FProcedureHandleGroup()
{
}

FProcedureHandleGroup::FProcedureHandleGroup(const TArray<FProcedureHandle>& InProcedureHandles)
	: ProcedureHandles(InProcedureHandles)
{
}

void FProcedureHandleGroup::CheckHandles()
{
	TArray<FProcedureHandle> Handles = ProcedureHandles;
	for (auto& Handle : Handles)
	{
		if (!IsValid(Handle.ProcedureObject))
		{
			ProcedureHandles.Remove(Handle);
		}
	}
}
