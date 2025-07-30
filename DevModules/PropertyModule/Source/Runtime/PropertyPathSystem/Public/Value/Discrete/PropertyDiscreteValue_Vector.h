// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Vector.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyDiscreteValue_Vector : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FVector GetVectorValue() const;
	PROPERTYPATHSYSTEM_API void SetVectorValue(const FVector& InValue);

	PROPERTYPATHSYSTEM_API FVector GetDefaultVectorValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultVectorValue(const FVector& InValue);
};
