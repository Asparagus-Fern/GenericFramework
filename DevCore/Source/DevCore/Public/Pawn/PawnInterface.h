// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnType.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

class AAIController;

UINTERFACE(MinimalAPI)
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IPawnInterface
{
	GENERATED_BODY()

public:
	IPawnInterface();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void AddLocation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void AddRotation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void AddZoom(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void SetLocation(FVector InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void SetRotation(FRotator InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	void SetZoom(float InValue);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	FVector GetLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	FRotator GetRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	float GetZoom();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	bool IsPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	bool IsAI();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	APlayerController* GetPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Pawn Interface")
	AAIController* GetAIController();
};
