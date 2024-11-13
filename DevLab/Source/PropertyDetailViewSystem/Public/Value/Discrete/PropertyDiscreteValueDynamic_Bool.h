// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Bool.generated.h"

/**
 * Bool类型属性
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Bool : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	UPropertyDiscreteValueDynamic_Bool();

public:
	void SetDefaultValue(bool Value);

	void SetTrueText(const FText& InText);
	void SetFalseText(const FText& InText);
};
