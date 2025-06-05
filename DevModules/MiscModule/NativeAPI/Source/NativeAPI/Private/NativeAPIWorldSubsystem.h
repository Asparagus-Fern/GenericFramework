// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPIInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "NativeAPIWorldSubsystem.generated.h"

class UNativeAPIProxyComponent;

/**
 * 
 */
UCLASS(MinimalAPI)
class UNativeAPIWorldSubsystem final : public UWorldSubsystem, public INativeAPIInterface
{
	GENERATED_BODY()

	friend class UNativeAPISubsystem;

public:
	static UNativeAPIWorldSubsystem* Get(const UWorld* World);
	
	// Begin USubsystem Interface.
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface.
	
	// Begin UWorldSubsystem Interface.
protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	// End UWorldSubsystem Interface.

	// Begin NativeAPI Interface.
	virtual void ProcessingNativeAPI(const FNativeAPIPayload& Payload) const override;
	// End NativeAPI Interface.
	
private:
	typedef TMap<UClass* , TArray<TObjectPtr<UNativeAPIProxyComponent>>> FNativeAPIProxyCollection;
	FNativeAPIProxyCollection NativeAPIProxyCollection;
	
	void RegisterNativeAPI(UNativeAPIProxyComponent* InProxy);
	void UnRegisterNativeAPI(UNativeAPIProxyComponent* InProxy);

	friend class UNativeAPIProxyComponent;
};