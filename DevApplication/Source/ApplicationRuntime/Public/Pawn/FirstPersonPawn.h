// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/DevPawn.h"
#include "FirstPersonPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Pawn_FP);

UCLASS()
class APPLICATIONRUNTIME_API AFirstPersonPawn : public ADevPawn
{
	GENERATED_BODY()

public:
	AFirstPersonPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	/* IPawnInterface */
public:
	virtual void AddRotation_Implementation(FVector2D InValue) override;
};
