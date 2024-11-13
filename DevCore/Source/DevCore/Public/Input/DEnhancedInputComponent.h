// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DEnhancedInputComponent.generated.h"


class UPlayerInputComponent;
class UInputHandle;

UCLASS()
class DEVCORE_API UDEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UDEnhancedInputComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
