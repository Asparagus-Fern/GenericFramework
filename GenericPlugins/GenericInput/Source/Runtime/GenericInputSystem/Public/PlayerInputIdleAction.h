// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Obect/GenericObject.h"
#include "PlayerInputIdleAction.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, MinimalAPI)
class UPlayerInputIdleAction : public UGenericObject, public FTickableGameObject
{
	GENERATED_BODY()

	/* FTickableGameObject */
protected:
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual void Tick(float DeltaTime) override;

	/* UPlayerInputIdleAction */
public:
	UFUNCTION(BlueprintCallable)
	GENERICINPUTSYSTEM_API void Start();

	UFUNCTION(BlueprintCallable)
	GENERICINPUTSYSTEM_API void Stop();

protected:
	GENERICINPUTSYSTEM_API virtual void HandleStartAction();
	GENERICINPUTSYSTEM_API virtual void HandleStopAction();
	GENERICINPUTSYSTEM_API virtual void HandleReverseAction();

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
	GENERICINPUTSYSTEM_API APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintPure)
	GENERICINPUTSYSTEM_API bool GetIsActionStart() const;

	UFUNCTION(BlueprintPure)
	GENERICINPUTSYSTEM_API bool GetIsActionReverse() const;

private:
	FTimerHandle WaitingTimerHandle;
	FTimerHandle ReverseMovementTimerHandle;
	bool bIsActionStart = false;
	bool bIsActionReverse = false;
	float ReverseTime = 0.f;
};
