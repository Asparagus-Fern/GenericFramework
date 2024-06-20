// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "CommonInputComponent.generated.h"


UCLASS()
class DEVCORE_API UCommonInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UCommonInputComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
