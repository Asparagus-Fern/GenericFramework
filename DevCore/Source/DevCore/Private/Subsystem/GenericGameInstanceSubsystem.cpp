// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Subsystem/GenericGameInstanceSubsystem.h"

bool UGenericGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGenericGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
