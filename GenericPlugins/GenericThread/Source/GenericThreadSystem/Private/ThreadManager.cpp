// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ThreadManager.h"

#include "GenericThread.h"
#include "StaticFunctions_Thread.h"
#include "ThreadType.h"

bool UThreadManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UThreadManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

#if WITH_EDITOR
	FEditorDelegates::EndPIE.AddUObject(this, &UThreadManager::EndPIE);
#endif

	FGenericThread::OnThreadRegisterEvent.AddUObject(this, &UThreadManager::RegisterThread);
}

void UThreadManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

#if WITH_EDITOR
	FEditorDelegates::EndPIE.RemoveAll(this);
#else
	KillAllThread();
#endif

	FGenericThread::OnThreadRegisterEvent.RemoveAll(this);
}

#if WITH_EDITOR

void UThreadManager::EndPIE(bool bIsSimulating)
{
}

#endif

void UThreadManager::KillAllThread()
{
	TArray<FGuid> AllThreadGuid;
	ThreadMapping.GetKeys(AllThreadGuid);

	for (const FGuid ThreadGuid : AllThreadGuid)
	{
		TSharedPtr<FGenericThread> Thread = GetThreadByGuid(ThreadGuid);
		if (Thread.IsValid())
		{
			Thread->Terminate();
		}
	}

	ThreadMapping.Empty();
}

void UThreadManager::RegisterThread(TSharedPtr<FGenericThread> Thread)
{
	if (!Thread.IsValid())
	{
		return;
	}

	ThreadMapping.Emplace(Thread->GetThreadGuid(), Thread);
	Thread->GetOnTerminated().AddUObject(this, &UThreadManager::OnThreadTerminated);
	Thread->GetOnCompleted().AddUObject(this, &UThreadManager::OnThreadCompleted);
}

void UThreadManager::UnRegisterThread(const TSharedPtr<FGenericThread>& Thread)
{
	if (!Thread.IsValid())
	{
		return;
	}

	Thread->GetOnTerminated().RemoveAll(this);
	Thread->GetOnCompleted().RemoveAll(this);
	ThreadMapping.Remove(Thread->GetThreadGuid());
}

void UThreadManager::OnThreadTerminated(FGuid ThreadGuid)
{
	auto Execute = [ThreadGuid, this]()
	{
		TSharedPtr<FGenericThread> Thread = ThreadMapping[ThreadGuid];
		UnRegisterThread(Thread);
	};

	AsyncTask(ENamedThreads::GameThread, Execute);
}

void UThreadManager::OnThreadCompleted(FGuid ThreadGuid)
{
	auto Execute = [ThreadGuid, this]()
	{
		TSharedPtr<FGenericThread> Thread = ThreadMapping[ThreadGuid];
		UnRegisterThread(Thread);
	};

	AsyncTask(ENamedThreads::GameThread, Execute);
}

TArray<FGuid> UThreadManager::GetAllThreadGuid() const
{
	TArray<FGuid> Result;
	ThreadMapping.GenerateKeyArray(Result);
	return Result;
}

TArray<TSharedPtr<FGenericThread>> UThreadManager::GetAllThreads() const
{
	TArray<TSharedPtr<FGenericThread>> Result;
	ThreadMapping.GenerateValueArray(Result);
	return Result;
}

TSharedPtr<FGenericThread> UThreadManager::GetThreadByGuid(const FGuid& ThreadGuid) const
{
	if (!ThreadMapping.Contains(ThreadGuid))
	{
		return nullptr;
	}
	return ThreadMapping[ThreadGuid];
}
