// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericThread.h"

FGenericThread::FGenericThread(const FString& InThreadName, const uint32 InThreadSize, const EThreadPriority InThreadPriority)
	: ThreadName(InThreadName),
	  ThreadSize(InThreadSize),
	  ThreadPriority(InThreadPriority),
	  Thread(nullptr),
	  bCreatePipe(false),
	  ReadPipe(nullptr),
	  WritePipe(nullptr),
	  bIsRunning(false),
	  bIsStoping(false),
	  SleepInterval(0.01f)
{
	ThreadGuid = FGuid::NewGuid();
}

FGenericThread::~FGenericThread()
{
}

bool FGenericThread::Launch()
{
	if (bIsRunning)
	{
		return false;
	}

	check(Thread == nullptr);

	OnBeginLaunch();

	static std::atomic<uint32> ThreadNameIndex{0};
	Thread = FRunnableThread::Create(this, *FString::Printf(TEXT("%s_%d"), *ThreadName, ThreadNameIndex.fetch_add(1)), ThreadSize, ThreadPriority);

	if (bCreatePipe && !FPlatformProcess::CreatePipe(ReadPipe, WritePipe))
	{
		return false;
	}

	const bool Result = OnThreadCreated(Thread);

	if (Result)
	{
		bIsRunning = true;

		if (!FPlatformProcess::SupportsMultithreading())
		{
			StartTime = FDateTime::UtcNow();
		}
	}

	return Result;
}

void FGenericThread::Update()
{
	if (!FPlatformProcess::SupportsMultithreading())
	{
		FPlatformProcess::Sleep(SleepInterval);

		if (bIsRunning)
		{
			RunInternal();
		}
	}
}

void FGenericThread::Cancel()
{
	StopInternal();
}

void FGenericThread::Terminate()
{
	if (bIsRunning)
	{
		Cancel();
	}

	if (Thread != nullptr)
	{
		Thread->WaitForCompletion();
		delete Thread;
	}
}

bool FGenericThread::Init()
{
	return FRunnable::Init();
}

uint32 FGenericThread::Run()
{
	StartTime = FDateTime::UtcNow();

	while (bIsRunning)
	{
		FPlatformProcess::Sleep(SleepInterval);
		RunInternal();
	}

	return 0;
}

void FGenericThread::Stop()
{
	FRunnable::Stop();
	StopInternal();
}

void FGenericThread::Exit()
{
	FRunnable::Exit();
}

void FGenericThread::RunInternal()
{
	ProcessOutput(FPlatformProcess::ReadPipe(ReadPipe));

	if (bIsStoping)
	{
		OnTerminated();
		OnTerminatedEvent.Broadcast(ThreadGuid);
		bIsRunning = false;
	}
	else
	{
		if (!IsThreadRunning())
		{
			CompleteInternal();
		}
	}
}

void FGenericThread::StopInternal()
{
	bIsStoping = true;
}

void FGenericThread::CompleteInternal()
{
	EndTime = FDateTime::UtcNow();

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
	ReadPipe = WritePipe = nullptr;

	OnCompleted();
	OnCompletedEvent.Broadcast(ThreadGuid);
	bIsRunning = false;
}

void FGenericThread::ProcessOutput(const FString& Output)
{
	OutputBuffer += Output;

	// if the delegate is not bound, then just keep buffering the output to OutputBuffer for later return from GetFullOutputWithoutDelegate()
	if (OnOutputEvent.IsBound())
	{
		// Output all the complete lines
		int32 LineStartIdx = 0;
		for (int32 Idx = 0; Idx < OutputBuffer.Len(); Idx++)
		{
			if (OutputBuffer[Idx] == '\r' || OutputBuffer[Idx] == '\n')
			{
				OnOutputEvent.Broadcast(OutputBuffer.Mid(LineStartIdx, Idx - LineStartIdx));

				if (OutputBuffer[Idx] == '\r' && Idx + 1 < OutputBuffer.Len() && OutputBuffer[Idx + 1] == '\n')
				{
					Idx++;
				}

				LineStartIdx = Idx + 1;
			}
		}

		// Remove all the complete lines from the buffer
		OutputBuffer.MidInline(LineStartIdx, MAX_int32, EAllowShrinking::No);
	}
}

FTimespan FGenericThread::GetDuration() const
{
	if (bIsRunning)
	{
		return FDateTime::UtcNow() - StartTime;
	}

	return EndTime - StartTime;
}
