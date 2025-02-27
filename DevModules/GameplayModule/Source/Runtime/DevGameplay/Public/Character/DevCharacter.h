// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/DevPawn.h"
#include "Pawn/Component/PawnInputMovementComponent.h"
#include "DevCharacter.generated.h"

UCLASS()
class DEVGAMEPLAY_API ADevCharacter : public ACharacter, public IPawnInterface, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	ADevCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInput) override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDelegate, ADevCharacter*)
	static FCharacterDelegate OnCharacterRegister;
	static FCharacterDelegate OnCharacterUnRegister;

	/* IPawnInterface */
public:
	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual bool IsPlayer() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual bool IsAI() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual APlayerController* GetPlayerController() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual AAIController* GetAIController() override;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure, Category="Character Input Movement")
	virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure, Category="Character Input Movement")
	virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure, Category="Character Input Movement")
	virtual float GetZoom() override;

	UFUNCTION(BlueprintPure, Category="Character Input Movement")
	virtual float GetZoomSpeedRate() override;

	/* IPawnLockStateInterface */
public:
	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual FPawnLockState GetPawnLockState() override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual bool CanMove(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual bool CanTurn(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual bool CanZoom(float TargetSpringArmLength) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual FVector GetLimitLocation(const FVector& TargetLocation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual FRotator GetLimitRotation(const FRotator& TargetRotation) const override;

	UFUNCTION(BlueprintPure, Category="Character Lock State")
	virtual float GetLimitSpringArmLength(float TargetSpringArmLength) const override;

	virtual void SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState) override;
	virtual void SetIsFullyLock_Implementation(bool InFullyLock) override;
	virtual void SetIsLockLocation_Implementation(bool InLockLocation) override;
	virtual void SetIsLockRotation_Implementation(bool InLockRotation) override;
	virtual void SetIsLockSpringArm_Implementation(bool InLockSpringArm) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnInputMovementComponent* InputMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnLockStateComponent* LockStateComponent = nullptr;
};
