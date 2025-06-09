// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MenuGenerationManager.h"

#include "Collection/MenuCollection.h"

bool UMenuGenerationManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UMenuGenerationManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UMenuGenerationManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UMenuGenerationManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UMenuCollection* UMenuGenerationManager::RegisterMenuCollection(TSubclassOf<UMenuCollection> InCollectionClass, bool InActived)
{
	UMenuCollection* NewCollection = NewObject<UMenuCollection>(this, InCollectionClass);
	RegisterMenuCollection(NewCollection, InActived);
	return NewCollection;
}

bool UMenuGenerationManager::RegisterMenuCollection(UMenuCollection* InCollection, bool InActived)
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InCollection Is InValid"))
		return false;
	}

	if (MenuCollections.Contains(InCollection))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InCollection Is Already Register"))
		return false;
	}

	InCollection->NativeOnCreate();
	MenuCollections.Add(InCollection);

	if (InActived)
	{
		InCollection->NativeOnActived();
	}

	return true;
}

bool UMenuGenerationManager::UnRegisterMenuCollection(UMenuCollection* InCollection)
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InCollection Is InValid"))
		return false;
	}

	if (!MenuCollections.Contains(InCollection))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InCollection Is Already UnRegister"))
		return false;
	}

	if (InCollection->GetIsActived())
	{
		InCollection->NativeOnInactived();
	}

	InCollection->NativeOnDestroy();
	MenuCollections.Remove(InCollection);

	return true;
}
