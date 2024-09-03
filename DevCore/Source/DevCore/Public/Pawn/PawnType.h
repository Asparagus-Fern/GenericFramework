// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PawnType.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPawnLocationLimit
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bLimitLocationX = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitLocationX"))
	FVector2D LocationXRange = FVector2D::Zero();

	UPROPERTY()
	bool bLimitLocationY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitLocationY"))
	FVector2D LocationYRange = FVector2D::Zero();

	UPROPERTY()
	bool bLimitLocationZ = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitLocationZ"))
	FVector2D LocationZRange = FVector2D::Zero();

public:
	bool CanMove(const FVector& TargetLocation) const;
	FVector GetLimitLocation(const FVector& TargetLocation) const;
	void UnLimit();
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPawnRotationLimit
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bLimitPitch = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitPitch", ClampMin = "-89.9", UIMin = "-89.9", ClampMax = "89.9", UIMax = "89.9"))
	FVector2D PitchRange = FVector2D(-89.9f, 10.f);

	UPROPERTY()
	bool bLimitYaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitYaw"))
	FVector2D YawRange = FVector2D::Zero();

public:
	bool CanTurn(const FRotator& TargetRotation) const;
	FRotator GetLimitRotation(const FRotator& TargetRotation) const;
	void UnLimit();
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSpringArmLimit
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bLimitSpringArmLength = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitSpringArmLength", ClampMin = "0.01", UIMin = "0.01"))
	FVector2D SpringArmLengthRange = FVector2D(0.01f, 1000000000.f);

public:
	bool CanZoom(float TargetSpringArmLength) const;
	float GetLimitSpringArmLength(float TargetSpringArmLength) const;
	void UnLimit();
};

USTRUCT(BlueprintType)
struct FPawnLockingState
{
	GENERATED_BODY()

	/* Lock */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFullyLock = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockSpringArm = false;

	/* Limit */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPawnLocationLimit PawnLocationLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPawnRotationLimit PawnRotationLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpringArmLimit SpringArmLimit;

public:
	bool CanMove(const FVector& TargetLocation) const;
	bool CanTurn(const FRotator& TargetRotation) const;
	bool CanZoom(float TargetSpringArmLength) const;
	void UnLock();
	void UnLimit();
};
