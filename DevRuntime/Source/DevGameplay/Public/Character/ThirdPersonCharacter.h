// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DevCharacter.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UPawnSpringArmComponent;
class UCameraComponent;

UCLASS()
class DEVGAMEPLAY_API AThirdPersonCharacter : public ADevCharacter
{
	GENERATED_BODY()

public:
	AThirdPersonCharacter();
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
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPawnSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
