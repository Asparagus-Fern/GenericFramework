// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Rotator.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Rotator : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FRotator GetRotatorValue() const;
	void SetRotatorValue(const FRotator& InValue);

	FRotator GetDefaultRotatorValue() const;
	void SetDefaultRotatorValue(const FRotator& InValue);
};
