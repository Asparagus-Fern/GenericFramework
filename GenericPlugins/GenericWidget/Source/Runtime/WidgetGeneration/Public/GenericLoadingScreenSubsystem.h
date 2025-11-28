// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/GenericGameInstanceSubsystem.h"
#include "GenericLoadingScreenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UGenericLoadingScreenSubsystem : public UGenericGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UGenericLoadingScreenSubsystem* Get(const UObject* WorldContextObject);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	virtual void PostLoadMapWithWorld(UWorld* InWorld);
	virtual void OnWorldBeginTearDown(UWorld* InWorld);
	virtual void OnExit();

public:
	void PlayLoadingScreen();
	void StopLoadingScreen();
};
