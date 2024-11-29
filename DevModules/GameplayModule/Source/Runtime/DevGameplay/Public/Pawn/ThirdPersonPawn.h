// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/DevPawn.h"
#include "ThirdPersonPawn.generated.h"

class UCameraComponent;
class UPawnSpringArmComponent;
class UCameraHandle;

UCLASS()
class DEVGAMEPLAY_API AThirdPersonPawn : public ADevPawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	UCameraComponent* DuplicateCameraComponent = nullptr;

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

	/* AThirdPersonPawn */
protected:
	virtual void OnSwitchCameraBegin(UCameraHandle* InCameraHandle);
	virtual void OnSwitchCameraFinish(UCameraHandle* InCameraHandle);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCameraComponent* GetActiveCameraComponent();
};
