// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PawnType.h"
#include "Component/PawnInputMovementComponent.h"
#include "Component/PawnLockStateComponent.h"
#include "GameFramework/Pawn.h"
#include "GenericPawn.generated.h"

class AAIController;
class UFloatingPawnMovement;

UINTERFACE(MinimalAPI)
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICGAMEPLAYSYSTEM_API IPawnInterface
{
	GENERATED_BODY()

public:
	IPawnInterface();

public:
	virtual bool IsPlayer() { return false; }
	virtual bool IsAI() { return false; }
	virtual APlayerController* GetPlayerController() { return nullptr; }
	virtual AAIController* GetAIController() { return nullptr; }
};

/**
 * 
 */
UCLASS()
class GENERICGAMEPLAYSYSTEM_API AGenericPawn : public APawn, public IPawnInterface, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	AGenericPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPawnDelegate, AGenericPawn*)
	static FPawnDelegate OnPawnRegister;
	static FPawnDelegate OnPawnUnRegister;

	/* IPawnInterface */
public:
	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	virtual bool IsPlayer() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	virtual bool IsAI() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	virtual APlayerController* GetPlayerController() override;

	UFUNCTION(BlueprintPure, Category="Pawn Basic")
	virtual AAIController* GetAIController() override;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual float GetZoom() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual float GetMovementSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual float GetRotationSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement")
	virtual float GetZoomSpeedRate() override;

	/* IPawnLockStateInterface */
public:
	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual FPawnLockState GetPawnLockState() override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual bool CanMove(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual bool CanTurn(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual bool CanZoom(float TargetSpringArmLength) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual FVector GetLimitLocation(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Pawn Lock State")
	virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const override;

	virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;
	virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName PawnName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFloatingPawnMovement* FloatingPawnMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnLockStateComponent* LockStateComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnInputMovementComponent* InputMovementComponent = nullptr;
};
