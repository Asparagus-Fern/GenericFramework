// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Input/InputType.h"
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

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	FVector GetLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	FRotator GetRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	float GetZoom();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	float GetMovementSpeedRate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	float GetRotationSpeedRate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	float GetZoomSpeedRate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	bool ReassessmentTargetArmLength();
};

/**
 * 对接增强输入，提供简单运动接口
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class DEVGAMEPLAY_API UPawnInputMovementComponent : public UActorComponent, public IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
	UPawnInputMovementComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnhanceInputMappingContext> EnhanceInputMappingContexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float MovementSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float RotationSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, UIMin = 0.1f))
	float ZoomSpeedRate = 1.f;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetupPlayerInput();

	UFUNCTION(BlueprintNativeEvent)
	void RemovePlayerInput();
};
