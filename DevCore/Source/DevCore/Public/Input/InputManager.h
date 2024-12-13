// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/TickableInternalManager.h"
#include "InputManager.generated.h"

class UPlayerInputBinding;
class UInputManager;
class UInputIdle;
class UDEnhancedInputComponent;
class UDEnhancedPlayerInput;

DECLARE_DELEGATE_OneParam(FInputIdleDelegate, UInputIdle*);

USTRUCT()
struct FInputIdleInfo
{
	GENERATED_BODY()

	friend UInputManager;

public:
	FInputIdleInfo();
	FInputIdleInfo(UInputIdle* InInputIdle, const FInputIdleDelegate& InIdle, const FInputIdleDelegate& InContinue);
	bool operator==(const FInputIdleInfo Other) const { return InputIdle == Other.InputIdle; }
	bool operator==(const UInputIdle* Other) const { return InputIdle == Other; }

public:
	bool bIsIdle = false;

	UPROPERTY()
	UInputIdle* InputIdle = nullptr;

	FInputIdleDelegate OnIdle;
	FInputIdleDelegate OnContinue;

protected:
	bool SwitchIdleState(float IdleTime);
	void Invalid() const;
};

/**
 * 
 */
UCLASS()
class DEVCORE_API UInputManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

	friend UDEnhancedPlayerInput;
	friend UDEnhancedInputComponent;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual void Tick(float DeltaTime) override;

	/* FCoreInternalManager */
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;
	
	/* IdleData */
public:
	bool RegisterIdleData(UInputIdle* InputIdle, const FInputIdleDelegate& OnIdle, const FInputIdleDelegate& OnContinue);
	void UnRegisterIdleData(UInputIdle* InputIdle);

	bool IsIdle(UInputIdle* InputIdle, bool& Idle);

protected:
	void RefreshIdleTime();
	float IdleTime = 0.f;

	UPROPERTY()
	TArray<FInputIdleInfo> InputIdleInfos;
};
