// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/PawnLockStateInterface.h"
#include "PawnLockStateComponent.generated.h"

/**
 * 提供对Pawn的移动旋转等限制锁定操作
 */
UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UPawnLockStateComponent : public UActorComponent, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	UPawnLockStateComponent();
	virtual void BeginPlay() override;

	/* IPawnLockStateInterface */
public:
	UFUNCTION(BlueprintPure)
	virtual FPawnLockState GetPawnLockState() override;

	UFUNCTION(BlueprintPure)
	virtual bool CanMove(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure)
	virtual bool CanTurn(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure)
	virtual bool CanZoom(float TargetSpringArmLength) const override;

	UFUNCTION(BlueprintPure)
	virtual FVector GetLimitLocation(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure)
	virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure)
	virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const override;

	virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;
	virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

public:
	UPROPERTY(EditAnywhere)
	FPawnLockState PawnLockState;
};
