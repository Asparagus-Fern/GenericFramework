// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/DevPawn.h"
#include "ThirdPersonPawn.generated.h"

class UCameraHandle;

UCLASS()
class APPLICATIONRUNTIME_API AThirdPersonPawn : public ADevPawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	UCameraComponent* DuplicateCameraComponent = nullptr;

	/* IPawnInterface */
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

	/* ADevPawn */
public:
	virtual UCameraComponent* GetActiveCameraComponent_Implementation() override;
	virtual void SetPawnLockingState_Implementation(FPawnLockingState InPawnLockingState) override;

	/* AThirdPersonPawn */
protected:
	virtual void OnSwitchCameraBegin(UCameraHandle* InCameraHandle);
	virtual void OnSwitchCameraFinish(UCameraHandle* InCameraHandle);
};
