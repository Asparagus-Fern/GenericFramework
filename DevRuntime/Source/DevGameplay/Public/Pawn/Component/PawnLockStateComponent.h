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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	FPawnLockState GetPawnLockState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetPawnLockState(const FPawnLockState& InPawnLockState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	bool CanMove(const FVector& TargetLocation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	bool CanTurn(const FRotator& TargetRotation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	bool CanZoom(float TargetSpringArmLength) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsFullyLock(bool InFullyLock);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockLocation(bool InLockLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockRotation(bool InLockRotation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	void SetIsLockSpringArm(bool InLockSpringArm);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	FVector GetLimitLocation(const FVector& TargetLocation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	FRotator GetLimitRotation(const FRotator& TargetRotation) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Lock State Interface")
	float GetLimitSpringArmLength(float TargetSpringArmLength) const;
};

/**
 * 
 */
UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class DEVGAMEPLAY_API UPawnLockStateComponent : public UActorComponent, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	UPawnLockStateComponent();
	virtual void BeginPlay() override;

	/* IPawnLockStateInterface */
public:
	virtual FPawnLockState GetPawnLockState_Implementation() override;
	virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;

	virtual bool CanMove_Implementation(const FVector& TargetLocation) const override;
	virtual bool CanTurn_Implementation(const FRotator& TargetRotation) const override;
	virtual bool CanZoom_Implementation(float TargetSpringArmLength) const override;

	virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

	virtual FVector GetLimitLocation_Implementation(const FVector& TargetLocation) const override;
	virtual FRotator GetLimitRotation_Implementation(const FRotator& TargetRotation) const override;
	virtual float GetLimitSpringArmLength_Implementation(float TargetSpringArmLength) const override;

public:
	UPROPERTY(EditAnywhere)
	FPawnLockState PawnLockState;
};
