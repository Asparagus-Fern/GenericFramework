// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Name.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UPropertyDiscreteValue_Name : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FName GetNameValue() const;
	PROPERTYPATHSYSTEM_API void SetNameValue(FName InValue);

	PROPERTYPATHSYSTEM_API FName GetDefaultNameValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultNameValue(FName InValue);
};
