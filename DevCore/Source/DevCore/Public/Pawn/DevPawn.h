// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInterface.h"
#include "GameFramework/Pawn.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "DevPawn.generated.h"

class UFloatingPawnMovement;

UCLASS()
class DEVCORE_API ADevPawn : public APawn, public IPawnInterface, public IProcedureBaseInterface
{
	GENERATED_BODY()

public:
	ADevPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
	
	/* IIPawnInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void SetLocation_Implementation(FVector InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual FVector GetLocation_Implementation() override;
	virtual FRotator GetRotation_Implementation() override;
	virtual FVector GetCameraLocation_Implementation() override;
	virtual FRotator GetCameraRotation_Implementation() override;

	/* ADevPawn */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* FloatingPawnMovement;

	UFUNCTION(BlueprintPure)
	APlayerController* GetPlayerController() const;
};
