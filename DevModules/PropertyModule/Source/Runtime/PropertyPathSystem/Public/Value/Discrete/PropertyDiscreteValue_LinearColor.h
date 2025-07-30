// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_LinearColor.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UPropertyDiscreteValue_LinearColor : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FLinearColor GetLinearColorValue() const;
	PROPERTYPATHSYSTEM_API void SetLinearColorValue(FLinearColor InValue);

	PROPERTYPATHSYSTEM_API FLinearColor GetDefaultLinearColorValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultLinearColorValue(FLinearColor InValue);
};
