// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInterface.h"
#include "PawnType.h"
#include "GameFramework/Pawn.h"
#include "Input/InputType.h"
#include "DevPawn.generated.h"

class UPlayerInputComponent;
class UInputHandle;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class UCommonSpringArmComponent;
class UFloatingPawnMovement;

UCLASS()
class DEVCORE_API ADevPawn : public APawn, public IPawnInterface
{
	GENERATED_BODY()

public:
	ADevPawn();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPawnDelegate, ADevPawn*)
	static FPawnDelegate OnPawnRegister;
	static FPawnDelegate OnPawnUnRegister;

	/* IIPawnInterface */
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

	virtual bool IsPlayer_Implementation() override;
	virtual bool IsAI_Implementation() override;
	virtual APlayerController* GetPlayerController_Implementation() override;
	virtual AAIController* GetAIController_Implementation() override;

	virtual UPlayerInputComponent* GetPlayerInputComponent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName PawnName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPawnLockingState PawnLockingState;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCameraComponent* GetActiveCameraComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPawnLockingState(FPawnLockingState InPawnLockingState);
};
