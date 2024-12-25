// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/HandleManager.h"

bool UHandleManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UHandleManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UHandleManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

UHandleBase* UHandleManager::RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass)
{
	UHandleBase* NewHandle = NewObject<UHandleBase>(Outer, InHandleClass);
	Handles.Add(NewHandle);
	return NewHandle;
}

UHandleBase* UHandleManager::RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FGuid InHandleID)
{
	if (!InHandleID.IsValid())
	{
		DLOG(DLogEvent, Error, TEXT("InHandleID Is Not Valid"))
		return nullptr;
	}

	UHandleBase* NewHandle = NewObject<UHandleBase>(Outer, InHandleClass);
	NewHandle->SetHandleID(InHandleID);
	Handles.Add(NewHandle);
	return NewHandle;
}

UHandleBase* UHandleManager::RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName)
{
	if (InHandleName == NAME_None)
	{
		DLOG(DLogEvent, Error, TEXT("InHandleName Is NULL"))
		return nullptr;
	}

	UHandleBase* NewHandle = NewObject<UHandleBase>(Outer, InHandleClass);
	NewHandle->SetHandleName(InHandleName);
	Handles.Add(NewHandle);
	return NewHandle;
}

void UHandleManager::UnRegisterHandle(UHandleBase* InHandle)
{
	if (IsHandleRegister(InHandle))
	{
		Handles.Remove(InHandle);
	}
}

void UHandleManager::UnRegisterHandle(FGuid InHandleID)
{
	if (IsHandleRegister(InHandleID))
	{
		Handles.Remove(GetHandle(InHandleID));
	}
}

void UHandleManager::UnRegisterHandle(FName InHandleName)
{
	if (IsHandleRegister(InHandleName))
	{
		Handles.Remove(GetHandle(InHandleName));
	}
}

bool UHandleManager::IsHandleRegister(const UHandleBase* InHandle)
{
	TArray<UHandleBase*> TempHandles = Handles;
	for (const auto& Handle : TempHandles)
	{
		if (IsValid(Handle) && Handle->GetHandleID() == InHandle->GetHandleID())
		{
			return true;
		}
	}

	return false;
}

bool UHandleManager::IsHandleRegister(FGuid InHandleID)
{
	if (!InHandleID.IsValid())
	{
		DLOG(DLogEvent, Error, TEXT("InHandleID Is Not Valid"))
		return false;
	}

	for (const auto& Handle : Handles)
	{
		if (Handle->GetHandleID() == InHandleID)
		{
			return true;
		}
	}

	return false;
}

bool UHandleManager::IsHandleRegister(FName InHandleName)
{
	if (InHandleName == NAME_None)
	{
		DLOG(DLogEvent, Error, TEXT("SequenceID Is NULL"))
		return false;
	}

	for (const auto& Handle : Handles)
	{
		if (Handle->GetHandleName() == InHandleName)
		{
			return true;
		}
	}

	return false;
}

UHandleBase* UHandleManager::GetHandle(FGuid InHandleID)
{
	if (!InHandleID.IsValid())
	{
		DLOG(DLogEvent, Error, TEXT("InHandleID Is Not Valid"))
		return nullptr;
	}

	for (const auto& Handle : Handles)
	{
		if (Handle->GetHandleID() == InHandleID)
		{
			return Handle;
		}
	}

	return nullptr;
}

UHandleBase* UHandleManager::GetHandle(FName InHandleName)
{
	if (InHandleName == NAME_None)
	{
		DLOG(DLogEvent, Error, TEXT("InHandleName Is NULL"))
		return nullptr;
	}

	for (const auto& Handle : Handles)
	{
		if (Handle->GetHandleName() == InHandleName)
		{
			return Handle;
		}
	}

	return nullptr;
}
