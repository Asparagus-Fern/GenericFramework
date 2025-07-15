// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonManager.h"

#include "GenericButtonCollection.h"
#include "GenericButtonGroup.h"
#include "GenericButtonWidget.h"
#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

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

UGenericButtonCollection* UGenericButtonManager::RegisterButtonCollection(TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	UGenericButtonCollection* NewCollection = NewObject<UGenericButtonCollection>(this, InCollectionClass);
	RegisterButtonCollection(NewCollection, InActived);
	return NewCollection;
}

bool UGenericButtonManager::RegisterButtonCollection(UGenericButtonCollection* InCollection, bool InActived)
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InCollection Is InValid"))
		return false;
	}

	if (Collections.Contains(InCollection))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InCollection Is Already Register"))
		return false;
	}

	InCollection->NativeOnCreate();
	Collections.Add(InCollection);

	if (InActived)
	{
		InCollection->NativeOnActived();
	}

	return true;
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
