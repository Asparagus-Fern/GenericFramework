// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Thread/GenericSingleThread.h"
// #include "ExtraProcThread.generated.h"

DECLARE_DELEGATE_TwoParams(FOnExtraProcCompleted, int32, uint16)

/**
 * 
 */
class FExtraProcThread : public FGenericSingleThread
{
	/* FExtraProcThread */
public:
	FExtraProcThread(const FString& InUrl, const FString& InParams, bool InRunInBackground, bool InCreatePipe);
	virtual ~FExtraProcThread() override;

public:
	void Cancle(bool KillTree = false);

	FProcHandle GetProcHandle() const;
	uint32 GetProcId() const;
	int32 GetReturnCode() const;
	FString GetCommandline() const;

	FOnExtraProcCompleted& OnExtraProcCompleted() { return ExtraProcCompletedDelegate; }

	/* FGenericThread */
protected:
	virtual void Stop() override;

	virtual void RunInternal() override;
	virtual void StopInternal() override;
	void StopInternal(bool KillTree = false);

	virtual bool OnLanch(FRunnableThread*& NewThread) override;
	virtual void OnStop() override;
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
	bool bCreatePipe;

	FOnExtraProcCompleted ExtraProcCompletedDelegate;
};
