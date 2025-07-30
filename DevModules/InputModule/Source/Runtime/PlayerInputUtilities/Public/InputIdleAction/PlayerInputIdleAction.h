// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/TickableObject.h"
#include "PlayerInputIdleAction.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, MinimalAPI)
class UPlayerInputIdleAction : public UTickableObject
{
	GENERATED_BODY()

	/* FTickableGameObject */
protected:
	PLAYERINPUTUTILITIES_API virtual bool IsTickable() const override;
	PLAYERINPUTUTILITIES_API virtual void Tick(float DeltaTime) override;

	/* UPlayerInputIdleAction */
public:
	UFUNCTION(BlueprintCallable)
	PLAYERINPUTUTILITIES_API void Start();

	UFUNCTION(BlueprintCallable)
	PLAYERINPUTUTILITIES_API void Stop();

protected:
	PLAYERINPUTUTILITIES_API virtual void HandleStartAction();
	PLAYERINPUTUTILITIES_API virtual void HandleStopAction();
	PLAYERINPUTUTILITIES_API virtual void HandleReverseAction();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionStop();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActionToggle(float DeltaTime, float Alpha);

public:
	/* If True, Action Will Reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableReverse = false;

	/* The Time To Start The Action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = 0, ClampMin = 0, Units = "s"))
	float ActionWaitTime = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0, ClampMin = 0, Units = "s"))
	float ReverseDuration = 10.f;

	/* Exclude Keys. Default Is Any Key Down Will Refresh The Timer. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FKey> ExcludeKeysWhenRefresh;

protected:
	UFUNCTION(BlueprintPure)
	PLAYERINPUTUTILITIES_API APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintPure)
	PLAYERINPUTUTILITIES_API bool GetIsActionStart() const;

	UFUNCTION(BlueprintPure)
	PLAYERINPUTUTILITIES_API bool GetIsActionReverse() const;

private:
	FTimerHandle WaitingTimerHandle;
	FTimerHandle ReverseMovementTimerHandle;
	bool bIsActionStart = false;
	bool bIsActionReverse = false;
	float ReverseTime = 0.f;
};
