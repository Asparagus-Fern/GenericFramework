// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Rotator.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Rotator : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	void SetDefaultValue(const FRotator& InValue);
	FRotator GetValue() const;
	void SetValue(const FRotator& InValue);
};
