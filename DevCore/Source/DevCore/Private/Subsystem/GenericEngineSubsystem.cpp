// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Subsystem/GenericEngineSubsystem.h"

bool UGenericEngineSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreDelegates::OnPostEngineInit.AddLambda([this]()
		{
			FCoreDelegates::OnPostEngineInit.RemoveAll(this);
			this->OnPostEngineInit();
		}
	);

	FWorldDelegates::OnStartGameInstance.AddLambda([this](UGameInstance* InGameInstance)
		{
			FWorldDelegates::OnStartGameInstance.RemoveAll(this);
			this->OnStartGameInstance(InGameInstance);
		}
	);
}

void UGenericEngineSubsystem::OnPostEngineInit()
{
}

void UGenericEngineSubsystem::OnStartGameInstance(UGameInstance* InGameInstance)
{
}

void UGenericEngineSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
}
