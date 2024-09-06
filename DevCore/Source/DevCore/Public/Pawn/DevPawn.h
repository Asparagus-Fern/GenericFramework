// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "PawnInterface.h"
#include "PawnType.h"
#include "GameFramework/Pawn.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "DevPawn.generated.h"

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName PawnName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPawnLockingState PawnLockingState;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Turn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Zoom;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCameraComponent* GetActiveCameraComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPawnLockingState(FPawnLockingState InPawnLockingState);

	/* Move */
protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnMoveStart(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnMoving(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnMoveEnd(const FInputActionValue& InValue);

	/* Turn */
protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnTurnStart(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnTurning(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnTurnEnd(const FInputActionValue& InValue);

	/* Zoom */
protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnZoomStart(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnZooming(const FInputActionValue& InValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnZoomEnd(const FInputActionValue& InValue);

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPawnDelegate, ADevPawn*)
	static FPawnDelegate OnPawnRegister;
	static FPawnDelegate OnPawnUnRegister;
};
