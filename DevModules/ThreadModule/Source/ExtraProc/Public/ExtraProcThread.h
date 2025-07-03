// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericSingleThread.h"
// #include "ExtraProcThread.generated.h"

/**
 * 
 */
class FExtraProcThread : public FGenericSingleThread
{
	/* FExtraProcThread */
public:
	FExtraProcThread(const FString& InUrl, const FString& InParams, bool InRunInBackground, bool TerminateWithParentProc, bool InCreatePipe);
	virtual ~FExtraProcThread() override;

	static TSharedPtr<FExtraProcThread> CreateThread(const FString& InUrl, const FString& InParams, bool InRunInBackground, bool TerminateWithParentProc, bool InCreatePipe)
	{
		return MakeShareable(new FExtraProcThread(InUrl, InParams, InRunInBackground, TerminateWithParentProc, InCreatePipe));
	}

public:
	FProcHandle GetProcHandle() const { return ProcHandle; }
	uint32 GetProcId() const { return ProcId; }
	int32 GetReturnCode() const { return ReturnCode; }
	bool GetKillTree() const { return bKillTree; }
	void SetKillTree(const bool KillTree) { bKillTree = KillTree; }
	FString GetUrl() const { return Url; }
	void SetUrl(const FString& InUrl) { Url = *InUrl; }
	FString GetParams() const { return Params; }
	void SetParams(const FString& InParams) { Params = *InParams; }
	bool GetRunInBackground() const { return bRunInBackground; }
	void SetRunInBackground(const bool RunInBackground) { bRunInBackground = RunInBackground; }
	bool GetTerminateWithParentProc() const { return bTerminateWithParentProc; }
	void SetTerminateWithParentProc(const bool TerminateWithParentProc) { bTerminateWithParentProc = TerminateWithParentProc; }
	FString GetCommandline() const { return FString::Printf(TEXT("%s %s"), Url, Params); }

	/* FGenericThread */
protected:
	virtual void OnBeginLaunch() override;
	virtual bool OnThreadCreated(FRunnableThread* InThread) override;
	virtual bool IsThreadRunning() override;
	virtual void OnTerminated() override;
	virtual void OnCompleted() override;

	/* FExtraProcThread */
protected:
	FProcHandle ProcHandle;
	uint32 ProcId;
	int32 ReturnCode;
	uint8 bKillTree : 1;

	const TCHAR* Url;
	const TCHAR* Params;
	bool bRunInBackground;
	bool bTerminateWithParentProc;
};
