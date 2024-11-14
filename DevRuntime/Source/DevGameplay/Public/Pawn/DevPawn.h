// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnType.h"
#include "Component/PawnInputMovementComponent.h"
#include "Component/PawnLockStateComponent.h"
#include "GameFramework/Pawn.h"
#include "DevPawn.generated.h"

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
class DEVGAMEPLAY_API IPawnInterface
{
	GENERATED_BODY()

public:
	IPawnInterface();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	bool IsPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	bool IsAI();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	APlayerController* GetPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	AAIController* GetAIController();
};

/**
 * 
 */
UCLASS()
class DEVGAMEPLAY_API ADevPawn : public APawn, public IPawnInterface, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	ADevPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPawnDelegate, ADevPawn*)
	static FPawnDelegate OnPawnRegister;
	static FPawnDelegate OnPawnUnRegister;

	/* IPawnInterface */
public:
	virtual bool IsPlayer_Implementation() override;
	virtual bool IsAI_Implementation() override;
	virtual APlayerController* GetPlayerController_Implementation() override;
	virtual AAIController* GetAIController_Implementation() override;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;
	virtual FVector GetLocation_Implementation() override;
	virtual FRotator GetRotation_Implementation() override;
	virtual float GetZoom_Implementation() override;
	virtual float GetMovementSpeedRate_Implementation() override;
	virtual float GetRotationSpeedRate_Implementation() override;
	virtual float GetZoomSpeedRate_Implementation() override;

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
