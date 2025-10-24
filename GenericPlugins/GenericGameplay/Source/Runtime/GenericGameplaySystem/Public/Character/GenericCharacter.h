// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PawnInputMovementInterface.h"
#include "Interface/PawnLockStateInterface.h"
#include "GenericCharacter.generated.h"

class UPawnLockStateComponent;
class UPawnInputMovementComponent;

UCLASS(MinimalAPI)
class AGenericCharacter : public ACharacter, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AGenericCharacter();
	GENERICGAMEPLAYSYSTEM_API virtual void SetupPlayerInputComponent(UInputComponent* PlayerInput) override;

	/* IPawnLockStateInterface */
public:
	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FPawnLockState GetPawnLockState() override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanMove(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanTurn(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual bool CanZoom(float TargetSpringArmLength) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FVector GetLimitLocation(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	GENERICGAMEPLAYSYSTEM_API virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const override;

	GENERICGAMEPLAYSYSTEM_API virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnInputMovementComponent* InputMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnLockStateComponent* LockStateComponent = nullptr;
};
