// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Color.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Color : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	void SetDefaultValue(FLinearColor InColor);
	void AddColorOption(FLinearColor InColor);
	void RemoveColorOption(FLinearColor InColor);
	FLinearColor GetValue() const;
	void SetValue(FLinearColor InColor);
};
