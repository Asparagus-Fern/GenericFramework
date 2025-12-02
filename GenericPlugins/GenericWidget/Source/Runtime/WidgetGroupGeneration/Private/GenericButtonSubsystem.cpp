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

bool UGenericButtonSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
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

void UGenericButtonSubsystem::UnRegisterAllButtonCollection()
{
	TArray<UGenericButtonCollection*> TempCollections = Collections;
	for (auto& Collection : TempCollections)
	{
		UnRegisterButtonCollection(Collection);
	}
}

bool UGenericButtonSubsystem::IsButtonCollectionRegistered(FGameplayTag InRootButtonTag)
{
	return IsButtonCollectionRegistered(GetButtonCollection(InRootButtonTag));
}

bool UGenericButtonSubsystem::IsButtonCollectionRegistered(UGenericButtonCollection* InCollection) const
{
	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InCollection Is InValid"))
		return false;
	}

	return Collections.Contains(InCollection);
}

TArray<UGenericButtonCollection*> UGenericButtonSubsystem::GetAllButtonCollection()
{
	return Collections;
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

TArray<UGenericButtonCollection*> UGenericButtonSubsystem::GetButtonCollections(const TArray<FGameplayTag>& InRootButtonTags)
{
	TArray<UGenericButtonCollection*> Result;

	for (auto& Collection : Collections)
	{
		if (InRootButtonTags.Contains(Collection->GetRootButtonTag()))
		{
			Result.Add(Collection);
		}
	}

	return Result;
}
