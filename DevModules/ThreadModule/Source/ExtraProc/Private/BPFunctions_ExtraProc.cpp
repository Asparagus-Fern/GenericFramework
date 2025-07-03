// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_ExtraProc.h"

#include "ExtraProcType.h"
#include "StaticFunctions_ExtraProc.h"

bool UBPFunctions_ExtraProc::LaunchExtraProc(const FProcStartUpInfo& Info, FThreadHandle& ProcHandle)
{
	FGuid ProcID;
	if (FStaticFunctions_ExtraProc::LaunchExtraProc(Info, ProcID))
	{
		ProcHandle = FThreadHandle(ProcID);
		return true;
	}

	return false;
}

void UBPFunctions_ExtraProc::TerminationExtraProc(FThreadHandle& ProcHandle, bool bKillTree)
{
	if (!ProcHandle.IsValid())
	{
		return;
	}

	FStaticFunctions_ExtraProc::TerminationExtraProc(ProcHandle.GetThreadGuid(), bKillTree);
	ProcHandle = FThreadHandle();
}
