// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "Misc/Timespan.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "ExtraProcManager.generated.h"

class FExtraProcThread;

static FString ExtrasPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras"));

/**
 * 
 */
UCLASS(MinimalAPI)
class UExtraProcManager : public UEngineSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
#if WITH_EDITOR
	void BeginPIE(bool bIsSimulating);
#endif

	void LaunchAllProc();
};
