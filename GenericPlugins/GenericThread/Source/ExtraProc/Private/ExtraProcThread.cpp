// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ExtraProcThread.h"

#include "Type/DebugType.h"
#include "Platform/WindowsExtraProcHelper.h"

FExtraProcThread::FExtraProcThread(const FString& InUrl, const FString& InParams, bool InRunInBackground, bool TerminateWithParentProc, bool InCreatePipe)
	: FGenericSingleThread(),
	  ProcId(MIN_uint32),
	  ReturnCode(0),
	  bKillTree(false),
	  Url(*InUrl),
	  Params(*InParams),
	  bRunInBackground(InRunInBackground),
	  bTerminateWithParentProc(TerminateWithParentProc)
{
	SetThreadName(TEXT("ExtraProcThread"));
	SetThreadSize(128 * 1024);
	SetThreadPriority(TPri_AboveNormal);
	SetIsCreatePipe(InCreatePipe);
}

FExtraProcThread::~FExtraProcThread()
{
}

void FExtraProcThread::OnBeginLaunch()
{
	FGenericSingleThread::OnBeginLaunch();
}

bool FExtraProcThread::OnThreadCreated(FRunnableThread* InThread)
{
	ProcHandle = FPlatformProcess::CreateProc(Url, Params, false, bRunInBackground, bRunInBackground, &ProcId, 0, *FPaths::GetPath(Url), WritePipe, ReadPipe);
	if (!ProcHandle.IsValid())
	{
		return false;
	}

	if (bTerminateWithParentProc)
	{
#if PLATFORM_WINDOWS
		if (!FWindowsExtraProcHelper::SetProcEndWithCurrentProcTermination(ProcHandle))
		{
			GenericLOG(GenericLogExtraProc, Warning, TEXT("Proc Add Job Fail."))
		}
#endif
	}

	return true;
}

bool FExtraProcThread::IsThreadRunning()
{
	return FGenericSingleThread::IsThreadRunning() && FPlatformProcess::IsProcRunning(ProcHandle);
}

void FExtraProcThread::OnTerminated()
{
	FGenericSingleThread::OnTerminated();

	bKillTree = true;
	FPlatformProcess::TerminateProc(ProcHandle, bKillTree);
}

void FExtraProcThread::OnCompleted()
{
	FGenericSingleThread::OnCompleted();

	if (!FPlatformProcess::GetProcReturnCode(ProcHandle, &ReturnCode))
	{
		ReturnCode = -1;
	}
}
