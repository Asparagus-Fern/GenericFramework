// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Text.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Text : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FText GetTextValue() const;
	void SetTextValue(const FText& InValue);

	FText GetDefaultTextValue() const;
	void SetDefaultTextValue(const FText& InValue);
};
