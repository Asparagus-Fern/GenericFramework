// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Name.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Name : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FName GetNameValue() const;
	void SetNameValue(FName InValue);

	FName GetDefaultNameValue() const;
	void SetDefaultNameValue(FName InValue);
};
