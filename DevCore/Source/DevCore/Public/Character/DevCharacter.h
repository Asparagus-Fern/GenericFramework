// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/PawnInterface.h"
#include "DevCharacter.generated.h"

class UPlayerInputComponent;

UCLASS()
class DEVCORE_API ADevCharacter : public ACharacter, public IPawnInterface
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
	FName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerInputComponent* PlayerInputComponent;
};
