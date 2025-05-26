// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_String.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_String : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FString GetStringValue() const;
	void SetStringValue(const FString& InValue);

	FString GetDefaultStringValue() const;
	void SetDefaultStringValue(const FString& InValue);
};
