// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnLockStateInterface.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitPitch", ClampMin = "-90", UIMin = "-90", ClampMax = "90", UIMax = "90"))
	FVector2D PitchRange = FVector2D(-90.f, 10.f);

	UPROPERTY()
	bool bLimitYaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitYaw", ClampMin = "0", UIMin = "0", ClampMax = "360", UIMax = "360"))
	FVector2D YawRange = FVector2D::Zero();

	UPROPERTY()
	bool bLimitRoll = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitRoll", ClampMin = "0", UIMin = "0", ClampMax = "360", UIMax = "360"))
	FVector2D RollRange = FVector2D::Zero();

public:
	bool CanTurn(const FRotator& TargetRotation) const;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLimitSpringArmLength", ClampMin = "0", UIMin = "0"))
	FVector2D SpringArmLengthRange = FVector2D(0.f, 100000000.f);

public:
	bool CanZoom(float TargetSpringArmLength) const;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICGAMEPLAYSYSTEM_API FPawnLockState
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
};

// This class does not need to be modified.
UINTERFACE()
class UPawnLockStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICGAMEPLAYSYSTEM_API IPawnLockStateInterface
{
	GENERATED_BODY()

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
