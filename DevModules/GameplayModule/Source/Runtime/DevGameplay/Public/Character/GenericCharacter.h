// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/GenericPawn.h"
#include "Component/PawnInputMovementComponent.h"
#include "GenericCharacter.generated.h"

UCLASS()
class DEVGAMEPLAY_API AGenericCharacter : public ACharacter, public IPawnInterface, public IPawnInputMovementInterface, public IPawnLockStateInterface
{
	GENERATED_BODY()

public:
	AGenericCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInput) override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterDelegate, AGenericCharacter*)
	static FCharacterDelegate OnCharacterRegister;
	static FCharacterDelegate OnCharacterUnRegister;

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
