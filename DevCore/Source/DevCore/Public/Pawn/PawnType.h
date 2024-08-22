// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PawnType.generated.h"

USTRUCT(BlueprintType)
struct FPawnLockingState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFullyLock = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation"))
	bool bLimitLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation && bLimitLocation"))
	FVector LimitMinLocation = FVector::Zero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation && bLimitLocation"))
	FVector LimitMaxLocation = FVector::Zero();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation"))
	bool bLimitRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation && bLimitRotation"))
	FRotator LimitMinRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation && bLimitRotation"))
	FRotator LimitMaxRotation = FRotator(360.f, 360.f, 0.f);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock"))
	bool bLockSpringArmIfExist = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockSpringArmIfExist"))
	bool bLimitSpringArmIfExist = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bFullyLock && !bLockLocation bLimitRotation"))
	FVector2D LimitSpringArmLength = FVector2D::Zero();

public:
	bool CanMove(const FVector& CurrentLocation) const;
	bool CanTurn(const FRotator& CurrentRotation) const;
	bool CanZoom(float CurrentSpringArmLength) const;
	void UnLock();
};
