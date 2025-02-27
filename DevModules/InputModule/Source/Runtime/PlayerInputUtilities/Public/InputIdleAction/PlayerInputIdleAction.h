// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/TickableObject.h"
#include "PlayerInputIdleAction.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class PLAYERINPUTUTILITIES_API UPlayerInputIdleAction : public UTickableObject
{
	GENERATED_BODY()

	/* FTickableGameObject */
protected:
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;

	/* UPlayerInputIdleAction */
public:
	UFUNCTION(BlueprintCallable)
	void Start();

	UFUNCTION(BlueprintCallable)
	void Stop();

protected:
	virtual void HandleStartAction();
	virtual void HandleStopAction();
	virtual void HandleReverseAction();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionStop();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionTriggle(float DeltaTime, float Alpha);

public:
	/* If True, Action Will Reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableReverse = false;

	/* The Time To Start The Action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = 0, ClampMin = 0, Units = "s"))
	float ActionWaitTime = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0, ClampMin = 0, Units = "s", EditConditionHides, EditCondition = "bEnableReverseMovement"))
	float ReverseDuration = 10.f;

	/* Exclude Keys. Default Is Any Key Down Will Refresh The Timer. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FKey> ExcludeKeysWhenRefresh;

protected:
	UFUNCTION(BlueprintPure)
	APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintPure)
	bool GetIsActionStart() const;

	UFUNCTION(BlueprintPure)
	bool GetIsActionReverse() const;

private:
	FTimerHandle WaitingTimerHandle;
	FTimerHandle ReverseMovementTimerHandle;
	bool bIsActionStart = false;
	bool bIsActionReverse = false;
	float ReverseTime = 0.f;
};
