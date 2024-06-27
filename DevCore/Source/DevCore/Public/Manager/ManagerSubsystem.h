// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ManagerSubsystem.generated.h"

class UCoreManager;

/**
 * 
 */
UCLASS()
class DEVCORE_API UManagerSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual UWorld* GetWorld() const override;
	static UManagerSubsystem* Get();

public:
	static bool bManagerSubsystemInitialize;

protected:
	FDelegateHandle PostWorldInitializationHandle;
	void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS);

	FDelegateHandle WorldMatchStartingHandle;
	virtual void OnWorldMatchStarting();

	FDelegateHandle WorldBeginTearDownHandle;
	virtual void OnWorldBeginTearDown(UWorld* InWorld);

public:
	UFUNCTION(BlueprintCallable)
	UCoreManager* RegisterManager(TSubclassOf<UCoreManager> InManagerClass);

	UFUNCTION(BlueprintCallable)
	void UnRegisterManager(TSubclassOf<UCoreManager> InManagerClass);

	UFUNCTION(BlueprintPure)
	bool IsManagerRegister(TSubclassOf<UCoreManager> InManagerClass, bool bAccurate = false);

	UFUNCTION(BlueprintPure)
	bool IsManagerActive(TSubclassOf<UCoreManager> InManagerClass, bool bAccurate = false);

	UFUNCTION(BlueprintPure, meta=(DeterminesOutputType = "InManagerClass"))
	UCoreManager* GetManager(TSubclassOf<UCoreManager> InManagerClass, bool bAccurate = false);

	UFUNCTION(BlueprintPure)
	TArray<UCoreManager*> GetManagers();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCoreManager*> Managers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCoreManager*> OverrideManagers;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWorld* World;
};
