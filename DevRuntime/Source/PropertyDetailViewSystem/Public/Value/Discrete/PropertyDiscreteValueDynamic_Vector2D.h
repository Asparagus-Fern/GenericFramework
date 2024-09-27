// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Vector2D.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Vector2D : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	void SetDefaultValue(const FVector2D& InValue);
	FVector2D GetValue() const;
	void SetValue(const FVector2D& InValue);
};
