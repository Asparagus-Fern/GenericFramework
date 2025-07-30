// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Rotator.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UPropertyDiscreteValue_Rotator : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FRotator GetRotatorValue() const;
	PROPERTYPATHSYSTEM_API void SetRotatorValue(const FRotator& InValue);

	PROPERTYPATHSYSTEM_API FRotator GetDefaultRotatorValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultRotatorValue(const FRotator& InValue);
};
