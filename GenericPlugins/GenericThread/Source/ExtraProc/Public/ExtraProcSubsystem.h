// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "Misc/Timespan.h"
#include "Subsystem/GenericEngineSubsystem.h"
#include "ExtraProcSubsystem.generated.h"

class FExtraProcThread;

static FString ExtrasPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras"));

/**
 * 
 */
UCLASS(MinimalAPI)
class UExtraProcSubsystem : public UGenericEngineSubsystem
{
	GENERATED_BODY()

public:
	static EXTRAPROC_API UExtraProcSubsystem* Get();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
#if WITH_EDITOR
	void BeginPIE(bool bIsSimulating);
#endif

protected:
	void LaunchAllProc();
	virtual FString GetExtrasPath();
};
