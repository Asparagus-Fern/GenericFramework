// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Color.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Color : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FColor GetColorValue() const;
	void SetColorValue(FColor InValue);

	FColor GetDefaultColorValue() const;
	void SetDefaultColorValue(FColor InValue);
};
