// Fill out your copyright notice in the Description page of Project Settings.


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

UMenuCollection* UMenuGenerationManager::RegisterMenuCollection(TSubclassOf<UMenuCollection> InCollection, bool InActived)
{
	UMenuCollection* NewCollection = NewObject<UMenuCollection>(this, InCollection);
	RegisterMenuCollection(NewCollection, InActived);
	return NewCollection;
}

void UMenuGenerationManager::RegisterMenuCollection(UMenuCollection* InCollection, bool InActived)
{
	if (!IsValid(InCollection))
	{
		DLOG(DLogUI, Error, TEXT("InCollection Is InValid"))
		return;
	}

	if (MenuCollections.Contains(InCollection))
	{
		DLOG(DLogUI, Warning, TEXT("InCollection Is Already Register"))
		return;
	}

	InCollection->NativeOnCreate();
	MenuCollections.Add(InCollection);

	if (InActived)
	{
		InCollection->NativeOnActived();
	}
}

void UMenuGenerationManager::UnRegisterMenuCollection(UMenuCollection* InCollection)
{
	if (!IsValid(InCollection))
	{
		DLOG(DLogUI, Error, TEXT("InCollection Is InValid"))
		return;
	}

	if (!MenuCollections.Contains(InCollection))
	{
		DLOG(DLogUI, Warning, TEXT("InCollection Is Already UnRegister"))
		return;
	}

	if (InCollection->GetIsActived())
	{
		InCollection->NativeOnInactived();
	}

	InCollection->NativeOnDestroy();
	MenuCollections.Remove(InCollection);
}
