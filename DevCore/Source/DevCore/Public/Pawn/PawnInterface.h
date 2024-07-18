// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

// This class does not need to be modified.
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	void AddLocation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	void AddRotation(FVector2D InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	void SetLocation(FVector InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	void SetRotation(FRotator InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	FVector GetLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	FRotator GetRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	FVector GetCameraLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="PawnInterface")
	FRotator GetCameraRotation();

public:
	virtual APawn* GetPawn();
	virtual FGameplayTag GetPawnTag();

public:
	void UpdateLockState(bool InLock, bool InLockLocation, bool InLockRotation);
	bool IsLock() const { return bLock || (bLockLocation && bLockRotation); }
	bool IsLockLocation() const { return bLock || bLockLocation; }
	bool IsLockRotation() const { return bLock || bLockRotation; }

protected:
	uint8 bLock : 1;
	uint8 bLockLocation : 1;
	uint8 bLockRotation : 1;

protected:
	virtual bool CanMove();
	virtual bool CanTurn();
};
