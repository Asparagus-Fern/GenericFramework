// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Color.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyDiscreteValue_Color : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FColor GetColorValue() const;
	PROPERTYPATHSYSTEM_API void SetColorValue(FColor InValue);

	PROPERTYPATHSYSTEM_API FColor GetDefaultColorValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultColorValue(FColor InValue);
};
