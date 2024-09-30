// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PropertyRegistry.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyRegistry : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintPure)
	// static TArray<FString> GetPropertyPath(TSubclassOf<UObject> );
};
