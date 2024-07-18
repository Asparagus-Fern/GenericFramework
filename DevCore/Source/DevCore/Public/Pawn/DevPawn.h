// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "PawnInterface.h"
#include "GameFramework/Pawn.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "DevPawn.generated.h"

class UFloatingPawnMovement;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Pawn);

UCLASS()
class DEVCORE_API ADevPawn : public APawn, public IPawnInterface, public IProcedureBaseInterface
{
	GENERATED_BODY()

public:
	ADevPawn();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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

	virtual APawn* GetPawn() override;
	virtual FGameplayTag GetPawnTag() override;

	/* ADevPawn */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Pawn"))
	FGameplayTag PawnTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* FloatingPawnMovement;

public:
	UFUNCTION(BlueprintPure)
	APlayerController* GetPlayerController() const;
};
