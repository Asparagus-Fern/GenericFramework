// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#include "BPFunctions/BPFunctions_Object.h"
#include "Procedure/ProcedureManagerSetting.h"
#include "Procedure/ProcedureProxy.h"

#define LOCTEXT_NAMESPACE "UProcedureManager"

bool UProcedureManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UProcedureManagerSetting::Get()->GetEnableManager();
}

void UProcedureManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	FProcedureDelegates::OnProxyHandleBegin.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleBegin);
	FProcedureDelegates::OnProxyHandlePause.AddUObject(this, &UProcedureManager::OnProcedureProxyHandlePause);
	FProcedureDelegates::OnProxyHandleContinue.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleContinue);
	FProcedureDelegates::OnProxyHandleStop.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleStop);
	FProcedureDelegates::OnProxyHandleFinish.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleFinish);
}

void UProcedureManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	FProcedureDelegates::OnProxyHandleBegin.RemoveAll(this);
	FProcedureDelegates::OnProxyHandlePause.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleContinue.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleStop.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleFinish.RemoveAll(this);
}

bool UProcedureManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(TArray<UProcedureObject*> InProcedureObjects, const bool InTargetActiveState, const FSimpleDelegate OnFinish)
{
	TArray<FProcedureHandle> ProcedureHandles;

	for (const auto& ProcedureObject : InProcedureObjects)
	{
		ProcedureHandles.Add(FProcedureHandle(ProcedureObject, InTargetActiveState));
	}

	return RegisterProcedureHandle(ProcedureHandles, OnFinish);
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(const TArray<FProcedureHandle> InProcedureHandles, const FSimpleDelegate OnFinish)
{
	FProcedureHandleGroup NewProcedureHandleGroup;

	NewProcedureHandleGroup.ProcedureHandles = InProcedureHandles;
	NewProcedureHandleGroup.OnFinish = OnFinish;

	return RegisterProcedureHandle(NewProcedureHandleGroup);
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(const FProcedureHandleGroup InHandleGroup)
{
	UProcedureProxy* NewProcedureHandle = NewObject<UProcedureProxy>(this);
	ActivatedProcedureProxy.Add(NewProcedureHandle);

	auto HandleNextTick = [NewProcedureHandle, InHandleGroup]()
	{
		NewProcedureHandle->Handle(InHandleGroup);
	};

	GetWorld()->GetTimerManager().SetTimerForNextTick(HandleNextTick);

	return NewProcedureHandle;
}

void UProcedureManager::OnProcedureProxyHandleBegin(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandlePause(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleContinue(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleStop(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleFinish(UProcedureProxy* InProcedureProxy)
{
	if (ActivatedProcedureProxy.Contains(InProcedureProxy))
	{
		ActivatedProcedureProxy.Remove(InProcedureProxy);
		InProcedureProxy->MarkAsGarbage();
	}
}

#undef LOCTEXT_NAMESPACE
