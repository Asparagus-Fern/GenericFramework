// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Vector.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Vector : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FVector GetVectorValue() const;
	void SetVectorValue(const FVector& InValue);

	FVector GetDefaultVectorValue() const;
	void SetDefaultVectorValue(const FVector& InValue);
};
