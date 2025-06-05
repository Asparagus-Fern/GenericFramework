// Copyright ChenTaiye 2025. All Rights Reserved.


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

	TArray<UHandleBase*> TempHandles = Handles;
	for (const auto& TempHandle : TempHandles)
	{
		UnRegisterHandle(TempHandle);
	}

	UnRegisterManager();
}

bool UHandleManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UHandleManager::RegisterHandle(UHandleBase* InHandle)
{
	if (!IsValid(InHandle))
	{
		return;
	}

	if (Handles.Contains(InHandle))
	{
		return;
	}

	Handles.Add(InHandle);
	InHandle->OnRegister();
}

UHandleBase* UHandleManager::RegisterHandle(TSubclassOf<UHandleBase> InHandleClass, FName InHandleName)
{
	return RegisterHandle(nullptr, InHandleClass, InHandleName);
}

UHandleBase* UHandleManager::RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName)
{
	UObject* HandleOuter = IsValid(Outer) ? Outer : this;
	UHandleBase* NewHandle = NewObject<UHandleBase>(HandleOuter, InHandleClass);

	if (InHandleName != NAME_None)
	{
		NewHandle->SetHandleName(InHandleName);
	}

	RegisterHandle(NewHandle);

	return NewHandle;
}

void UHandleManager::UnRegisterHandle(UHandleBase* InHandle)
{
	if (IsHandleRegister(InHandle))
	{
		InHandle->OnUnRegister();
		Handles.Remove(InHandle);
	}
}

void UHandleManager::UnRegisterHandle(FGuid InHandleID)
{
	if (IsHandleRegister(InHandleID))
	{
		UnRegisterHandle(GetHandle(InHandleID));
	}
}

void UHandleManager::UnRegisterHandle(FName InHandleName)
{
	if (IsHandleRegister(InHandleName))
	{
		UnRegisterHandle(GetHandle(InHandleName));
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
		GenericLOG(EventLog, Error, TEXT("InHandleID Is Not Valid"))
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
		GenericLOG(EventLog, Error, TEXT("SequenceID Is NULL"))
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
		GenericLOG(EventLog, Error, TEXT("InHandleID Is Not Valid"))
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
		GenericLOG(EventLog, Error, TEXT("InHandleName Is NULL"))
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
