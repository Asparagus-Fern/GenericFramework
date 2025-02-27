// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pawn/PawnType.h"
#include "PawnLockStateComponent.generated.h"

UINTERFACE(MinimalAPI)
class UPawnLockStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVGAMEPLAY_API IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	IPawnLockStateInterface();

public:
	virtual FPawnLockState GetPawnLockState() { return FPawnLockState(); }

	virtual bool CanMove(const FVector& TargetLocation) const { return false; }
	virtual bool CanTurn(const FRotator& TargetRotation) const { return false; }
	virtual bool CanZoom(float TargetSpringArmLength) const { return false; }

	virtual FVector GetLimitLocation(const FVector& TargetLocation) const { return FVector::ZeroVector; }
	virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const { return FRotator::ZeroRotator; }
	virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const { return 0.f; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetPawnLockState(const FPawnLockState& InPawnLockState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsFullyLock(bool InFullyLock);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockLocation(bool InLockLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockRotation(bool InLockRotation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockSpringArm(bool InLockSpringArm);
};

/**
 * 提供对Pawn的移动旋转等限制锁定操作
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class DEVGAMEPLAY_API UPawnLockStateComponent : public UActorComponent, public IPawnLockStateInterface
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
