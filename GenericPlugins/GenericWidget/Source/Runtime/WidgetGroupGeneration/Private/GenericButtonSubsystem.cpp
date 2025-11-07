// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonSubsystem.h"

#include "GenericButtonCollection.h"
#include "GenericWidgetSubsystem.h"

UGenericButtonSubsystem* UGenericButtonSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

UGenericButtonCollection* UGenericButtonSubsystem::RegisterButtonCollection(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	check(Player)

	UGenericButtonCollection* NewCollection = NewObject<UGenericButtonCollection>(Player, InCollectionClass);
	NewCollection->NativeOnCreate();
	Collections.Add(NewCollection);

	if (InActived)
	{
		NewCollection->SetIsActived(true);
	}

	return NewCollection;
}

bool UGenericButtonSubsystem::IsButtonCollectionRegistered(UGenericButtonCollection* InCollection) const
{
	return Collections.Contains(InCollection);
}

bool UGenericButtonSubsystem::UnRegisterButtonCollection(UGenericButtonCollection* InCollection)
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
		InCollection->SetIsActived(false);
	}

	InCollection->NativeOnDestroy();
	Collections.Remove(InCollection);

	return true;
}

UGenericButtonCollection* UGenericButtonSubsystem::GetButtonCollection(FGameplayTag InRootButtonTag)
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


