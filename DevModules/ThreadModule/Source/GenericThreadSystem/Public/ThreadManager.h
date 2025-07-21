// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/EngineSubsystem.h"
#include "ThreadManager.generated.h"

class FGenericThread;

/**
 * 
 */
UCLASS()
class GENERICTHREADSYSTEM_API UThreadManager : public UEngineSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
#if WITH_EDITOR
	void EndPIE(bool bIsSimulating);
#endif

	void KillAllThread();

private:
	void RegisterThread(TSharedPtr<FGenericThread> Thread);
	void UnRegisterThread(const TSharedPtr<FGenericThread>& Thread);

	void OnThreadTerminated(FGuid ThreadGuid);
	void OnThreadCompleted(FGuid ThreadGuid);

public:
	TArray<FGuid> GetAllThreadGuid() const;
	TArray<TSharedPtr<FGenericThread>> GetAllThreads() const;
	TMap<FGuid, TSharedPtr<FGenericThread>> GetThreadMapping() const { return ThreadMapping; }
	TSharedPtr<FGenericThread> GetThreadByGuid(const FGuid& ThreadGuid) const;

	template <typename T>
	TSharedPtr<T> GetThread(const FGuid& ThreadGuid)
	{
		return StaticCastSharedPtr<T>(GetThreadByGuid(ThreadGuid));
	}

private:
	TMap<FGuid, TSharedPtr<FGenericThread>> ThreadMapping;
};
