// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_Thread.h"

#include "GenericThread.h"
#include "ThreadManager.h"
#include "Manager/ManagerStatics.h"

bool UBPFunctions_Thread::IsThreadValid(const FThreadHandle& ThreadHandle)
{
	if (!ThreadHandle.IsValid())
	{
		return false;
	}

	if (UThreadManager* ThreadManager = GetManager<UThreadManager>())
	{
		TSharedPtr<FGenericThread> Thread = ThreadManager->GetThreadByGuid(ThreadHandle.GetThreadGuid());
		return Thread.IsValid();
	}

	return false;
}

bool UBPFunctions_Thread::IsThreadRunning(const FThreadHandle& ThreadHandle)
{
	if (!ThreadHandle.IsValid())
	{
		return false;
	}

	if (UThreadManager* ThreadManager = GetManager<UThreadManager>())
	{
		TSharedPtr<FGenericThread> Thread = ThreadManager->GetThreadByGuid(ThreadHandle.GetThreadGuid());
		return Thread->GetIsRunning();
	}

	return false;
}

bool UBPFunctions_Thread::GetThreadName(const FThreadHandle& ThreadHandle, FString& ThreadName)
{
	if (!ThreadHandle.IsValid())
	{
		return false;
	}

	if (UThreadManager* ThreadManager = GetManager<UThreadManager>())
	{
		TSharedPtr<FGenericThread> Thread = ThreadManager->GetThreadByGuid(ThreadHandle.GetThreadGuid());
		ThreadName = Thread->GetThreadName();

		return true;
	}

	return false;
}

bool UBPFunctions_Thread::GetThreadDuration(const FThreadHandle& ThreadHandle, FTimespan& Duration)
{
	if (!ThreadHandle.IsValid())
	{
		return false;
	}

	if (UThreadManager* ThreadManager = GetManager<UThreadManager>())
	{
		TSharedPtr<FGenericThread> Thread = ThreadManager->GetThreadByGuid(ThreadHandle.GetThreadGuid());
		Duration = Thread->GetDuration();

		return true;
	}

	return false;
}

bool UBPFunctions_Thread::EqualEqual_ThreadHandle(const FThreadHandle& A, const FThreadHandle& B)
{
	return A == B;
}

bool UBPFunctions_Thread::NotEqual_ThreadHandle(const FThreadHandle& A, const FThreadHandle& B)
{
	return A != B;
}
