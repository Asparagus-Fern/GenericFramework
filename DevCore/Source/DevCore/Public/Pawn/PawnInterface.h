// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddLocation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddRotation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FRotator GetRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetLocation(FVector InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetRotation(FRotator InValue);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RefreshTransform();
};
