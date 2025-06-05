// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPIInterface.h"
#include "NativeAPITypes.h"
#include "Subsystems/EngineSubsystem.h"
#include "NativeAPISubsystem.generated.h"

class UNativeAPIObject;
class UWorld;
class UGameInstance;

/**
 *
 */
UCLASS()
class UNativeAPISubsystem final : public UEngineSubsystem, public INativeAPIInterface
{
	GENERATED_BODY()

public:
	// Begin USubsystem Interface.
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface.

	UFUNCTION(BlueprintCallable, Category = NativeAPI)
	void SendSimulationNativeAPI(const FString& NativeAPIJson);

protected:
	// Begin NativeAPI Interface.
	virtual void ProcessingNativeAPI(const FNativeAPIPayload& Payload) const override;
	// End NativeAPI Interface.

private:
#if WITH_EDITOR
	void HandleOnPostPIEStarted(bool bIsSimulating);
	void HandleOnEndPIE(bool bIsSimulating);
#else
    void HandleOnStartGameInstance(UGameInstance* InGameInstance);
    void HandleOnEnginePreExit();
#endif

	// void HandleOnNativeAPISessionFeatureRegistered(const FName& FeatureName, IModularFeature* Feature);
	void StartAllFeatureSession();
	void EndAllFeatureSession();

	void HandleOnReceiveNativePayload(const FNativeAPIPayload& InPayload);
};
