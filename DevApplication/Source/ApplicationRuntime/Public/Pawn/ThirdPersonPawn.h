// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/DevPawn.h"
#include "GameplayTagContainer.h"
#include "ThirdPersonPawn.generated.h"

class UCameraHandle;
class ACameraPointBase;
class USphereComponent;
class UCommonSpringArmComponent;
class UCameraComponent;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Pawn_TP);

UCLASS()
class APPLICATIONRUNTIME_API AThirdPersonPawn : public ADevPawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCommonSpringArmComponent* CommonSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraCacheComponent;

public:
	UFUNCTION(BlueprintPure)
	UCameraComponent* GetActiveCameraComponent() const;

	/* IProcedureBaseInterface */
public:
	virtual void OnRefresh_Implementation() override;

	/* IIPawnInterface */
public:
	virtual void AddLocation_Implementation(FVector2D InValue) override;
	virtual void AddRotation_Implementation(FVector2D InValue) override;
	virtual void SetRotation_Implementation(FRotator InValue) override;
	virtual FRotator GetRotation_Implementation() override;
	virtual FRotator GetCameraRotation_Implementation() override;

	/* FCameraPointDelegates */
public:
	virtual void OnSwitchCameraFinish(UCameraHandle* InCameraHandle);

	/* AThirdPersonPawn */
protected:
	void RefreshSpringArmComponent();
	virtual bool GetHitResult(FHitResult& HitResult);
};
