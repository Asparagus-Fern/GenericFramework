// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputConfigurationComponent.h"
#include "Components/ActorComponent.h"
#include "PawnInputMovementComponent.generated.h"

UINTERFACE(MinimalAPI)
class UPawnInputMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVGAMEPLAY_API IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
	IPawnInputMovementInterface();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void AddLocation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void AddRotation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void AddZoom(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void SetLocation(FVector InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void SetRotation(FRotator InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	void SetZoom(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	bool ReassessmentFocus();

public:
	virtual FVector GetLocation() { return FVector::ZeroVector; }
	virtual FRotator GetRotation() { return FRotator::ZeroRotator; }
	virtual float GetZoom() { return 0.f; }

public:
	virtual float GetMovementSpeedRate() { return 0.f; }
	virtual float GetRotationSpeedRate() { return 0.f; }
	virtual float GetZoomSpeedRate() { return 0.f; }
};

/**
 * 对接增强输入，提供简单运动接口
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UPawnInputMovementComponent : public UPlayerInputConfigurationComponent, public IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
	UPawnInputMovementComponent();

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure)
	virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure)
	virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure)
	virtual float GetZoom() override;

	UFUNCTION(BlueprintPure)
	virtual float GetMovementSpeedRate() override;

	UFUNCTION(BlueprintPure)
	virtual float GetRotationSpeedRate() override;

	UFUNCTION(BlueprintPure)
	virtual float GetZoomSpeedRate() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float MovementSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float RotationSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float ZoomSpeedRate = 1.f;
};
