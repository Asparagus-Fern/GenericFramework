// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_GenericButtonWidget.h"

#include "GenericButtonCollection.h"
#include "GenericButtonSubsystem.h"


UGenericButtonCollection* UBPFunctions_GenericButtonWidget::RegisterButtonCollectionByClass(const UObject* WorldContextObject, APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	if (!IsValid(Player))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Player Is InValid"))
		return nullptr;
	}

	if (!InCollectionClass)
	{
		GenericLOG(GenericLogUI, Error, TEXT("CollectionClass Is InValid"))
		return nullptr;
	}

	if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(WorldContextObject))
	{
		return Cast<UGenericButtonCollection>(GenericButtonSubsystem->RegisterButtonCollection(Player, InCollectionClass, InActived));
	}

	return nullptr;
}

bool UBPFunctions_GenericButtonWidget::UnRegisterButtonCollection(const UObject* WorldContextObject, UGenericButtonCollection* InCollection)
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Collection Is InValid"))
		return false;
	}

	if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(WorldContextObject))
	{
		return GenericButtonSubsystem->UnRegisterButtonCollection(InCollection);
	}

	return false;
}

bool UBPFunctions_GenericButtonWidget::IsButtonCollectionRegistered(const UObject* WorldContextObject, UGenericButtonCollection* InCollection, bool& IsRegistered)
{
	if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(WorldContextObject))
	{
		IsRegistered = GenericButtonSubsystem->IsButtonCollectionRegistered(InCollection);
		return true;
	}
	return false;
}

bool UBPFunctions_GenericButtonWidget::GetAllButtonCollection(const UObject* WorldContextObject, TArray<UGenericButtonCollection*>& Collections)
{
	if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(WorldContextObject))
	{
		Collections = GenericButtonSubsystem->GetAllButtonCollection();
		return true;
	}
	return false;
}

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::GetButtonCollectionByTag(const UObject* WorldContextObject, TSubclassOf<UGenericButtonCollection> InCollectionClass, FGameplayTag InRootButtonTag)
{
	if (!InCollectionClass)
	{
		GenericLOG(GenericLogUI, Error, TEXT("CollectionClass Is InValid"))
		return nullptr;
	}

	if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(WorldContextObject))
	{
		return Cast<UGenericButtonCollection>(GenericButtonSubsystem->GetButtonCollection(InRootButtonTag));
	}

	return nullptr;
}
