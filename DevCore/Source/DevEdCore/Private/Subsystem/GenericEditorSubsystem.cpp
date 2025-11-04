// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Subsystem/GenericEditorSubsystem.h"

bool UGenericEditorSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGenericEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
