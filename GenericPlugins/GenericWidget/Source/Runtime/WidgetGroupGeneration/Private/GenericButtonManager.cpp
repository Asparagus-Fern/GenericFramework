// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonManager.h"

#include "GenericButtonCollection.h"
#include "GenericButtonGroup.h"
#include "GenericWidgetManager.h"

bool UGenericButtonManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericButtonManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UGenericButtonManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UGenericButtonManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UGenericButtonCollection* UGenericButtonManager::RegisterButtonCollection(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	check(Player)

	UGenericButtonCollection* NewCollection = NewObject<UGenericButtonCollection>(Player, InCollectionClass);
	NewCollection->NativeOnCreate();
	Collections.Add(NewCollection);

	if (InActived)
	{
		NewCollection->NativeOnActived();
	}

	return NewCollection;
}

bool UGenericButtonManager::UnRegisterButtonCollection(UGenericButtonCollection* InCollection)
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InCollection Is InValid"))
		return false;
	}

	if (!Collections.Contains(InCollection))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InCollection Is Already UnRegister"))
		return false;
	}

	if (InCollection->GetIsActived())
	{
		InCollection->NativeOnInactived();
	}

	InCollection->NativeOnDestroy();
	Collections.Remove(InCollection);

	return true;
}

UGenericButtonCollection* UGenericButtonManager::GetButtonCollection(FGameplayTag InRootButtonTag)
{
	for (auto& Collection : Collections)
	{
		if (Collection->GetRootButtonTag() == InRootButtonTag)
		{
			return Collection;
		}
	}
	return nullptr;
}
