// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_LinearColor.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_LinearColor : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FLinearColor GetLinearColorValue() const;
	void SetLinearColorValue(FLinearColor InValue);

	FLinearColor GetDefaultLinearColorValue() const;
	void SetDefaultLinearColorValue(FLinearColor InValue);
};
