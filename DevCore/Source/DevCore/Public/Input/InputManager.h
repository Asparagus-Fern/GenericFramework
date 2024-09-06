// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "InputManager.generated.h"

class UInputManager;
class UInputIdle;
class UCommonInputComponent;
class UCommonPlayerInput;

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
class DEVCORE_API UInputManager : public UCoreManager
{
	GENERATED_UCLASS_BODY()
	friend UCommonPlayerInput;
	friend UCommonInputComponent;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* FTickableGameObject */
public:
	virtual void Tick(float DeltaTime) override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UInputManager */
public:
	bool RegisterIdleData(UInputIdle* InputIdle, const FInputIdleDelegate& OnIdle, const FInputIdleDelegate& OnContinue);
	void UnRegisterIdleData(UInputIdle* InputIdle);

protected:
	void RefreshIdleTime();
	float IdleTime = 0.f;

	UPROPERTY()
	TArray<FInputIdleInfo> InputIdleInfos;
};
