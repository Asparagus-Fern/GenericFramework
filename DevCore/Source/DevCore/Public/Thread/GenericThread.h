// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
// #include "GenericThread.generated.h"

DECLARE_DELEGATE_OneParam(FOnThreadOutput, FString)

/**
 * 
 */
class DEVCORE_API FGenericThread : public FRunnable
{
public:
	FGenericThread(bool InCreatePipe);
	virtual ~FGenericThread() override;

	/* FRunnable */
protected:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

	/* FGenericThread */
public:
	virtual bool Launch();
	bool Update();
	void Cancle();
	void Kill();

	FDateTime GetStartTime() const;
	FTimespan GetDuration() const;

	bool IsRunning() const;
	float GetSleepInterval() const;
	void SetSleepInterval(float InSleepInterval);

	FSimpleDelegate& OnThreadTerminate() { return TerminateDelegate; };
	FSimpleDelegate& OnThreadCompleted() { return CompletedDelegate; }
	FOnThreadOutput& OnThreadOutput() { return OutputDelegate; }

protected:
	virtual void RunInternal();
	virtual void StopInternal();

	virtual bool OnLanch(FRunnableThread*& NewThread);
	virtual void OnStop();
	virtual void OnCompleted();

private:
	void ProcessOutput(const FString& Output);

protected:
	FRunnableThread* Thread;

	uint8 bCreatePipe : 1;
	void* ReadPipe;
	void* WritePipe;

	FDateTime StartTime;
	FDateTime EndTime;

	uint8 bIsRunning : 1;
	float SleepInterval;

	uint8 bStoping : 1;
	FSimpleDelegate TerminateDelegate;

	FSimpleDelegate CompletedDelegate;

	FString OutputBuffer;
	FOnThreadOutput OutputDelegate;
};
