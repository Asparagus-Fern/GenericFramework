// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ExtraProcThread.h"

FExtraProcThread::FExtraProcThread(const FString& InUrl, const FString& InParams, bool InRunInBackground, bool InCreatePipe)
	: FGenericSingleThread(InCreatePipe),
	  ProcId(MIN_uint32),
	  ReturnCode(0),
	  bKillTree(false),
	  Url(*InUrl),
	  Params(*InParams),
	  bRunInBackground(InRunInBackground),
	  bCreatePipe(InCreatePipe)
{
}

FExtraProcThread::~FExtraProcThread()
{
}

void FExtraProcThread::Cancle(bool KillTree)
{
	StopInternal(KillTree);
}

FProcHandle FExtraProcThread::GetProcHandle() const
{
	return ProcHandle;
}

uint32 FExtraProcThread::GetProcId() const
{
	return ProcId;
}

int32 FExtraProcThread::GetReturnCode() const
{
	return ReturnCode;
}

FString FExtraProcThread::GetCommandline() const
{
	return FString::Printf(TEXT("%s %s"), Url, Params);
}

void FExtraProcThread::Stop()
{
	StopInternal(true);
}

void FExtraProcThread::RunInternal()
{
	FGenericSingleThread::RunInternal();

	if (!bStoping && !FPlatformProcess::IsProcRunning(ProcHandle))
	{
		OnCompleted();
	}
}

void FExtraProcThread::StopInternal()
{
	FGenericSingleThread::StopInternal();
}

void FExtraProcThread::StopInternal(bool KillTree)
{
	FGenericSingleThread::StopInternal();
	bKillTree = KillTree;
}

bool FExtraProcThread::OnLanch(FRunnableThread*& NewThread)
{
	ProcHandle = FPlatformProcess::CreateProc(Url, Params, false, bRunInBackground, bRunInBackground, &ProcId, 0, *FPaths::GetPath(Url), WritePipe, ReadPipe);
	if (!ProcHandle.IsValid())
	{
		return false;
	}

	static std::atomic<uint32> ExtraProcIndex{0};
	const FString ExtraProcName = FString::Printf(TEXT("FExtraProc %d"), ExtraProcIndex.fetch_add(1));
	Thread = FRunnableThread::Create(this, *ExtraProcName, 128 * 1024, TPri_AboveNormal);

	return true;
}

void FExtraProcThread::OnStop()
{
	FPlatformProcess::TerminateProc(ProcHandle, bKillTree);
}

void FExtraProcThread::OnCompleted()
{
	if (!FPlatformProcess::GetProcReturnCode(ProcHandle, &ReturnCode))
	{
		ReturnCode = -1;
	}

	ExtraProcCompletedDelegate.ExecuteIfBound(ReturnCode, (uint16)ProcId);

	FGenericSingleThread::OnCompleted();
}
