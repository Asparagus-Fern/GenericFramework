// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Vector.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Vector : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	void SetDefaultValue(const FVector& InValue);
	FVector GetValue() const;
	void SetValue(const FVector& InValue);
};
