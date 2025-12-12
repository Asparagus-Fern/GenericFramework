// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/PawnInputMovementInterface.h"
#include "Interface/PawnLockStateInterface.h"
#include "GenericPawn.generated.h"

class UPawnInputMovementComponent;
class UPawnLockStateComponent;
class UFloatingPawnMovement;

/**
 * 
 */
UCLASS(MinimalAPI)
class AGenericPawn : public APawn, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AGenericPawn(const FObjectInitializer& ObjectInitializer);

	/* IPawnInputMovementInterface */
public:
	GENERICGAMEPLAYSYSTEM_API virtual void AddLocation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddRotation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddZoom_Implementation(float InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetLocation_Implementation(FVector InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetRotation_Implementation(FRotator InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual float GetZoom() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual float GetMovementBaseSpeed() override;
	
	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual float GetMovementSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual float GetRotationSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	GENERICGAMEPLAYSYSTEM_API virtual float GetZoomSpeedRate() override;

	/* IPawnLockStateInterface */
public:
	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FPawnLockState GetPawnLockState() override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanMove(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanTurn(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanZoom(float TargetSpringArmLength) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FVector GetLimitLocation(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const override;

	GENERICGAMEPLAYSYSTEM_API virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFloatingPawnMovement* FloatingPawnMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnLockStateComponent* LockStateComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnInputMovementComponent* InputMovementComponent = nullptr;
};
