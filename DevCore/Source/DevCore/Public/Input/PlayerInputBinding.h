// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInputBinding.generated.h"

class UCommonInputComponent;

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class DEVCORE_API UPlayerInputBinding : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerIndex = 0;

public:
	virtual void SetupBinding(UCommonInputComponent* CommonInputComponent);
	virtual void ClearupBinding(UCommonInputComponent* CommonInputComponent);
};
