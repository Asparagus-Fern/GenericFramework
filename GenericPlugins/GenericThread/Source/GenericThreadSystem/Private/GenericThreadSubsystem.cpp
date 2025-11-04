// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericThreadSubsystem.h"

#include "GenericThread.h"

UGenericThreadSubsystem* UGenericThreadSubsystem::Get()
{
	return GEngine->GetEngineSubsystem<UGenericThreadSubsystem>();
}

void UGenericThreadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

#if WITH_EDITOR
	FEditorDelegates::EndPIE.AddUObject(this, &UGenericThreadSubsystem::EndPIE);
#endif

	FGenericThread::OnThreadRegisterEvent.AddUObject(this, &UGenericThreadSubsystem::RegisterThread);
}

void UGenericThreadSubsystem::Deinitialize()
{
	Super::Deinitialize();

#if WITH_EDITOR
	FEditorDelegates::EndPIE.RemoveAll(this);
#else
	KillAllThread();
#endif

	FGenericThread::OnThreadRegisterEvent.RemoveAll(this);
}

#if WITH_EDITOR

void UGenericThreadSubsystem::EndPIE(bool bIsSimulating)
{
}

#endif

void UGenericThreadSubsystem::KillAllThread()
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

void UGenericThreadSubsystem::RegisterThread(TSharedPtr<FGenericThread> Thread)
{
	if (!Thread.IsValid())
	{
		return;
	}

	ThreadMapping.Emplace(Thread->GetThreadGuid(), Thread);
	Thread->GetOnTerminated().AddUObject(this, &UGenericThreadSubsystem::OnThreadTerminated);
	Thread->GetOnCompleted().AddUObject(this, &UGenericThreadSubsystem::OnThreadCompleted);
}

void UGenericThreadSubsystem::UnRegisterThread(const TSharedPtr<FGenericThread>& Thread)
{
	if (!Thread.IsValid())
	{
		return;
	}

	Thread->GetOnTerminated().RemoveAll(this);
	Thread->GetOnCompleted().RemoveAll(this);
	ThreadMapping.Remove(Thread->GetThreadGuid());
}

void UGenericThreadSubsystem::OnThreadTerminated(FGuid ThreadGuid)
{
	auto Execute = [ThreadGuid, this]()
	{
		TSharedPtr<FGenericThread> Thread = ThreadMapping[ThreadGuid];
		UnRegisterThread(Thread);
	};

	AsyncTask(ENamedThreads::GameThread, Execute);
}

void UGenericThreadSubsystem::OnThreadCompleted(FGuid ThreadGuid)
{
	auto Execute = [ThreadGuid, this]()
	{
		TSharedPtr<FGenericThread> Thread = ThreadMapping[ThreadGuid];
		UnRegisterThread(Thread);
	};

	AsyncTask(ENamedThreads::GameThread, Execute);
}

TArray<FGuid> UGenericThreadSubsystem::GetAllThreadGuid() const
{
	TArray<FGuid> Result;
	ThreadMapping.GenerateKeyArray(Result);
	return Result;
}

TArray<TSharedPtr<FGenericThread>> UGenericThreadSubsystem::GetAllThreads() const
{
	TArray<TSharedPtr<FGenericThread>> Result;
	ThreadMapping.GenerateValueArray(Result);
	return Result;
}

TSharedPtr<FGenericThread> UGenericThreadSubsystem::GetThreadByGuid(const FGuid& ThreadGuid) const
{
	if (!ThreadMapping.Contains(ThreadGuid))
	{
		return nullptr;
	}
	return ThreadMapping[ThreadGuid];
}
