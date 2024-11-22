// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_SetLevelLocation.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_SetLevelLocation : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector NewLocation = FVector::ZeroVector;
};
