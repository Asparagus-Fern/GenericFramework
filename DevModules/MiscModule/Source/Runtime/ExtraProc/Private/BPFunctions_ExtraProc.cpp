// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_ExtraProc.h"

#include "ExtraProcType.h"
#include "ExtraProcManager.h"
#include "Manager/ManagerStatics.h"

bool UBPFunctions_ExtraProc::IsValid(const FExtraProcHandle& InHandle)
{
	if (const UExtraProcManager* ExtraProcManager = GetManager<UExtraProcManager>())
	{
		return ExtraProcManager->IsProcValid(InHandle);
	}

	return false;
}

bool UBPFunctions_ExtraProc::IsRunning(const FExtraProcHandle& InHandle)
{
	if (const UExtraProcManager* ExtraProcManager = GetManager<UExtraProcManager>())
	{
		return ExtraProcManager->IsProcRunning(InHandle);
	}

	return false;
}

FTimespan UBPFunctions_ExtraProc::GetDuration(const FExtraProcHandle& InHandle)
{
	if (const UExtraProcManager* ExtraProcManager = GetManager<UExtraProcManager>())
	{
		return ExtraProcManager->GetDuration(InHandle);
	}

	return FTimespan::Zero();
}

bool UBPFunctions_ExtraProc::ExecuteExtraProc(const FProcStartUpInfo& Info, FExtraProcHandle& OutHandle)
{
	if (UExtraProcManager* ExtraProcManager = GetManager<UExtraProcManager>())
	{
		return ExtraProcManager->LaunchExtraProc(Info, OutHandle);
	}

	return false;
}

void UBPFunctions_ExtraProc::TerminationExtraProc(FExtraProcHandle& InHandle, bool bKillTree)
{
	if (UExtraProcManager* ExtraProcManager = GetManager<UExtraProcManager>())
	{
		return ExtraProcManager->TerminationExtraProc(InHandle, bKillTree);
	}
}

bool UBPFunctions_ExtraProc::EqualEqual_ExtraProcHandle(const FExtraProcHandle& A, const FExtraProcHandle& B)
{
	return A == B;
}

bool UBPFunctions_ExtraProc::NotEqual_ExtraProcHandle(const FExtraProcHandle& A, const FExtraProcHandle& B)
{
	return A != B;
}
