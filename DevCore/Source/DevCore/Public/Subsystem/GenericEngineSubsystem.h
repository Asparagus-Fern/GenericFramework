// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "GenericEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGenericEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnPostEngineInit(); //Delegate Broadcast From FCoreDelegates::OnPostEngineInit
	virtual void OnStartGameInstance(UGameInstance* InGameInstance); //Delegate Broadcast From FWorldDelegates::OnStartGameInstance
	virtual void Deinitialize() override;
};
