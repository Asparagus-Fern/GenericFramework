// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DevCharacter.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DEVGAMEPLAY_API AThirdPersonCharacter : public ADevCharacter
{
	GENERATED_BODY()

public:
	AThirdPersonCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
