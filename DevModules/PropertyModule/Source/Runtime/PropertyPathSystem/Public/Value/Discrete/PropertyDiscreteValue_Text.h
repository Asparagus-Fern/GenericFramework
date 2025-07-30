// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Text.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyDiscreteValue_Text : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FText GetTextValue() const;
	PROPERTYPATHSYSTEM_API void SetTextValue(const FText& InValue);

	PROPERTYPATHSYSTEM_API FText GetDefaultTextValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultTextValue(const FText& InValue);
};
