// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInputMovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPawnInputMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICGAMEPLAYSYSTEM_API IPawnInputMovementInterface
{
	GENERATED_BODY()

public:
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Input Movement Interface")
	bool ReassessmentFocus();

public:
	virtual FVector GetLocation() { return FVector::ZeroVector; }
	virtual FRotator GetRotation() { return FRotator::ZeroRotator; }
	virtual float GetZoom() { return 0.f; }

public:
	virtual float GetMovementSpeedRate() { return 0.f; }
	virtual float GetRotationSpeedRate() { return 0.f; }
	virtual float GetZoomSpeedRate() { return 0.f; }
};
