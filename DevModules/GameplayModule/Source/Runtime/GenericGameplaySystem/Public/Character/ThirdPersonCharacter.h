// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GenericCharacter.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UPawnSpringArmComponent;
class UCameraComponent;

UCLASS(MinimalAPI)
class AThirdPersonCharacter : public AGenericCharacter
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AThirdPersonCharacter();
	GENERICGAMEPLAYSYSTEM_API virtual void BeginPlay() override;
	GENERICGAMEPLAYSYSTEM_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IPawnInputMovementInterface */
public:
	GENERICGAMEPLAYSYSTEM_API virtual void AddLocation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddRotation_Implementation(FVector2D InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void AddZoom_Implementation(float InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetLocation_Implementation(FVector InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetRotation_Implementation(FRotator InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual void SetZoom_Implementation(float InValue) override;
	GENERICGAMEPLAYSYSTEM_API virtual FVector GetLocation() override;
	GENERICGAMEPLAYSYSTEM_API virtual FRotator GetRotation() override;
	GENERICGAMEPLAYSYSTEM_API virtual float GetZoom() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPawnSpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
