// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GenericSingleThread.h"

FGenericSingleThread::FGenericSingleThread(const FString& InThreadName, const uint32 InThreadSize, const EThreadPriority InThreadPriority)
	: FGenericThread(InThreadName, InThreadSize, InThreadPriority)
{
}

FGenericSingleThread::~FGenericSingleThread()
{
}

void FGenericSingleThread::Tick()
{
	if (GetIsRunning())
	{
		RunInternal();
	}
}
