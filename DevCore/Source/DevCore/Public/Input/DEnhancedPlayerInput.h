// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "DEnhancedPlayerInput.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UDEnhancedPlayerInput : public UEnhancedPlayerInput
{
	GENERATED_BODY()

public:
	virtual bool InputKey(const FInputKeyParams& Params) override;
};
