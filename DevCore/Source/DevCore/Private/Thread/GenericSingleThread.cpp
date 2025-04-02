// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Thread/GenericSingleThread.h"

FGenericSingleThread::FGenericSingleThread(bool InCreatePipe)
	: FGenericThread(InCreatePipe)
{
}

FGenericSingleThread::~FGenericSingleThread()
{
}

void FGenericSingleThread::Tick()
{
	if (IsRunning())
	{
		RunInternal();
	}
}
