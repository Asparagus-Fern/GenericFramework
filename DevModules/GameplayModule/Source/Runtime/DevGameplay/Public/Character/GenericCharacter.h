// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/DevPawn.h"
#include "GenericCharacter.generated.h"

class UGameplayCameraComponent;
class UPawnInputMovementComponent;



UCLASS()
class DEVGAMEPLAY_API AGenericCharacter : public ACharacter, public IPawnInterface, public IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
	AGenericCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IPawnInterface */
public:
	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual bool IsPlayer() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual bool IsAI() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual APlayerController* GetPlayerController() override;

	UFUNCTION(BlueprintPure, Category="Character Basic")
	virtual AAIController* GetAIController() override;

	/* IPawnInputMovementInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void AddZoom_Implementation(float InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual void SetZoom_Implementation(float InValue) override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual FVector GetLocation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual FRotator GetRotation() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual float GetZoom() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual float GetMovementSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual float GetRotationSpeedRate() override;

	UFUNCTION(BlueprintPure, Category="Pawn Input Movement Interface")
	virtual float GetZoomSpeedRate() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGameplayCameraComponent* GameplayCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPawnInputMovementComponent* InputMovementComponent;
};
