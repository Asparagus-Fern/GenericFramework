// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_String.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UPropertyDiscreteValue_String : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FString GetStringValue() const;
	PROPERTYPATHSYSTEM_API void SetStringValue(const FString& InValue);

	PROPERTYPATHSYSTEM_API FString GetDefaultStringValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultStringValue(const FString& InValue);
};
