// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Thread/GenericThread.h"

FGenericThread::FGenericThread(bool InCreatePipe)
	: Thread(nullptr),
	  bCreatePipe(InCreatePipe),
	  ReadPipe(nullptr),
	  WritePipe(nullptr),
	  bIsRunning(false),
	  SleepInterval(0.01f),
	  bStoping(false)
{
}

FGenericThread::~FGenericThread()
{
	Kill();
}

bool FGenericThread::Init()
{
	return FRunnable::Init();
}

uint32 FGenericThread::Run()
{
	StartTime = FDateTime::UtcNow();

	while (IsRunning())
	{
		FPlatformProcess::Sleep(SleepInterval);
		RunInternal();
	}

	return 0;
}

void FGenericThread::Exit()
{
	FRunnable::Exit();
}

void FGenericThread::Stop()
{
	StopInternal();
}

bool FGenericThread::Launch()
{
	if (bIsRunning)
	{
		return false;
	}

	check(Thread == nullptr);

	if (bCreatePipe && !FPlatformProcess::CreatePipe(ReadPipe, WritePipe))
	{
		return false;
	}

	const bool Result = OnLanch(Thread);

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

bool FGenericThread::Update()
{
	const bool Running = IsRunning();

	if (!FPlatformProcess::SupportsMultithreading())
	{
		FPlatformProcess::Sleep(SleepInterval);

		if (Running)
		{
			RunInternal();
		}
	}

	return Running;
}

void FGenericThread::Cancle()
{
	StopInternal();
}

void FGenericThread::Kill()
{
	if (IsRunning())
	{
		Cancle();
	}

	if (Thread != nullptr)
	{
		Thread->WaitForCompletion();
		delete Thread;
	}
}

FTimespan FGenericThread::GetDuration() const
{
	if (IsRunning())
	{
		return FDateTime::UtcNow() - StartTime;
	}

	return EndTime - StartTime;
}

FDateTime FGenericThread::GetStartTime() const
{
	return StartTime;
}

bool FGenericThread::IsRunning() const
{
	return bIsRunning;
}

float FGenericThread::GetSleepInterval() const
{
	return SleepInterval;
}

void FGenericThread::SetSleepInterval(float InSleepInterval)
{
	SleepInterval = InSleepInterval;
}

void FGenericThread::RunInternal()
{
	ProcessOutput(FPlatformProcess::ReadPipe(ReadPipe));

	if (bStoping)
	{
		OnStop();
		TerminateDelegate.ExecuteIfBound();
		bIsRunning = false;
	}
}

void FGenericThread::StopInternal()
{
	bStoping = true;
}

bool FGenericThread::OnLanch(FRunnableThread*& NewThread)
{
	return false;
}

void FGenericThread::OnStop()
{
}

void FGenericThread::OnCompleted()
{
	EndTime = FDateTime::UtcNow();

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
	ReadPipe = WritePipe = nullptr;

	CompletedDelegate.ExecuteIfBound();
	bIsRunning = false;
}

void FGenericThread::ProcessOutput(const FString& Output)
{
	OutputBuffer += Output;

	// if the delegate is not bound, then just keep buffering the output to OutputBuffer for later return from GetFullOutputWithoutDelegate()
	if (OutputDelegate.IsBound())
	{
		// Output all the complete lines
		int32 LineStartIdx = 0;
		for (int32 Idx = 0; Idx < OutputBuffer.Len(); Idx++)
		{
			if (OutputBuffer[Idx] == '\r' || OutputBuffer[Idx] == '\n')
			{
				OutputDelegate.ExecuteIfBound(OutputBuffer.Mid(LineStartIdx, Idx - LineStartIdx));

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
