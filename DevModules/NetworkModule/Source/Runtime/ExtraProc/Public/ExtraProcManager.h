// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "ExtraProcManager.generated.h"

class FExtraProcThread;

static FString ExtrasPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras"));

/**
 * 
 */
UCLASS()
class EXTRAPROC_API UExtraProcManager : public UEngineSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void LanchAllProc();
	void KillAllProc();

#if WITH_EDITOR
	void BeginPIE(bool bIsSimulating);
	void EndPIE(bool bIsSimulating);
#endif

public:
	bool IsProcValid(const FExtraProcHandle& InHandle) const;
	bool IsProcRunning(const FExtraProcHandle& InHandle) const;
	FTimespan GetDuration(const FExtraProcHandle& InHandle) const;

	bool LaunchExtraProc(const FProcStartUpInfo& Info, FExtraProcHandle& ProcHandle);
	bool LaunchExtraProc(const FProcStartUpInfo& Info, uint16& ProcId);
	bool LaunchExtraProc(const FString& Urls, const FString& Params, bool RunInBackground, bool CreatePipe, bool ShouldEndWithParentProcTermination, uint16& OutProcId);

	void TerminationExtraProc(FExtraProcHandle& ProcHandle, bool bKillTree = false);
	void TerminationExtraProc(uint16 ProcId, bool bKillTree = false);

private:
	void OnExtraProcCompleted(int32 ReturnCode, uint16 ProcId);

private:
	TMap<uint16, TSharedPtr<FExtraProcThread>> ExtraProcHandle;
};
