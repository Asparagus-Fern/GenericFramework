// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "GenericThreadRaw.generated.h"

class FGenericThread;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnThreadRegister, TSharedPtr<FGenericThread>)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnThreadTerminated, FGuid)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnThreadCompleted, FGuid)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnThreadOutput, FString)

/**
 * 
 */
class GENERICTHREADSYSTEM_API FGenericThread : public FRunnable
{
public:
	FGenericThread(const FString& InThreadName = TEXT("GenericThread"), uint32 InThreadSize = 0, EThreadPriority InThreadPriority = EThreadPriority::TPri_Normal);
	virtual ~FGenericThread() override;

	inline static FOnThreadRegister OnThreadRegisterEvent;

	static TSharedPtr<FGenericThread> CreateThread(const FString& InThreadName, uint32 InThreadSize = 0, EThreadPriority InThreadPriority = EThreadPriority::TPri_Normal)
	{
		return MakeShareable(new FGenericThread(InThreadName, InThreadSize, InThreadPriority));
	}

public:
	bool Launch();
	void Update();
	void Cancel();
	void Terminate();

private:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

protected:
	void RunInternal();
	void StopInternal();
	void CompleteInternal();

protected:
	virtual void OnBeginLaunch() { return; }
	virtual bool OnThreadCreated(FRunnableThread* InThread) { return true; }
	virtual bool IsThreadRunning() { return true; }
	virtual void OnTerminated() { return; }
	virtual void OnCompleted() { return; }

private:
	void ProcessOutput(const FString& Output);

public:
	FGuid GetThreadGuid() const { return ThreadGuid; }
	FString GetThreadName() { return ThreadName; }
	void SetThreadName(const FString& InThreadName) { ThreadName = InThreadName; }
	uint32 GetThreadSize() const { return ThreadSize; }
	void SetThreadSize(const uint32 InThreadSize) { ThreadSize = InThreadSize; }
	EThreadPriority GetThreadPriority() const { return ThreadPriority; }
	void SetThreadPriority(const EThreadPriority InThreadPriority) { ThreadPriority = InThreadPriority; }
	bool GetIsCreatePipe() const { return bCreatePipe; }
	void SetIsCreatePipe(bool CreatePipe) { bCreatePipe = CreatePipe; }
	FDateTime GetStartTime() const { return StartTime; }
	FDateTime GetEndTime() const { return EndTime; }
	FTimespan GetDuration() const;
	bool GetIsRunning() const { return bIsRunning; }
	float GetSleepInterval() const { return SleepInterval; }
	void SetSleepInterval(const float InSleepInterval) { SleepInterval = InSleepInterval; }
	FOnThreadTerminated& GetOnTerminated() { return OnTerminatedEvent; }
	FOnThreadCompleted& GetOnCompleted() { return OnCompletedEvent; }
	FString GetOutput() { return OutputBuffer; }
	FOnThreadOutput& GetOnOutput() { return OnOutputEvent; }

protected:
	FGuid ThreadGuid;
	FString ThreadName;
	uint32 ThreadSize;
	EThreadPriority ThreadPriority;
	FRunnableThread* Thread;

	uint8 bCreatePipe : 1;
	void* ReadPipe;
	void* WritePipe;

	FDateTime StartTime;
	FDateTime EndTime;

	uint8 bIsRunning : 1;
	uint8 bIsStoping : 1;
	float SleepInterval;

	FOnThreadTerminated OnTerminatedEvent;
	FOnThreadCompleted OnCompletedEvent;

	FString OutputBuffer;
	FOnThreadOutput OnOutputEvent;
};
