// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Subsystem/GenericLocalPlayerSubsystem.h"

bool UGenericLocalPlayerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGenericLocalPlayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGenericLocalPlayerSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);
	Player = NewPlayerController;
}
