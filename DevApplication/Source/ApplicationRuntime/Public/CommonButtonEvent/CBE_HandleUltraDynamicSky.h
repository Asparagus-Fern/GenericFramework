// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleUltraDynamicSky.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleUltraDynamicSky : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TArray<FName, FString> Values;
};
