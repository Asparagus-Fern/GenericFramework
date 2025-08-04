// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/PawnInterface.h"
#include "Interface/PawnInputMovementInterface.h"
#include "Interface/PawnLockStateInterface.h"
#include "Interface/PlayerIdentityInterface.h"
#include "GenericPawn.generated.h"

class UPawnInputMovementComponent;
class UPawnLockStateComponent;
class UFloatingPawnMovement;

/**
 * 
 */
UCLASS(MinimalAPI)
class AGenericPawn : public APawn, public IPlayerIdentityInterface, public IPawnInterface, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AGenericPawn(const FObjectInitializer& ObjectInitializer);

	/* IPlayerIdentityInterface */
public:
	UFUNCTION(BlueprintPure)
	GENERICGAMEPLAYSYSTEM_API virtual int32 GetPlayerIdentity() override;

	UFUNCTION(BlueprintPure)
	GENERICGAMEPLAYSYSTEM_API virtual const FUniqueNetIdRepl& GetPlayerUniqueIdentity() override;

	/* IPawnInterface */
public:
	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	GENERICGAMEPLAYSYSTEM_API virtual bool IsPlayer() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	GENERICGAMEPLAYSYSTEM_API virtual bool IsAI() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	GENERICGAMEPLAYSYSTEM_API virtual APlayerController* GetPlayerController() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	GENERICGAMEPLAYSYSTEM_API virtual AAIController* GetAIController() override;

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
