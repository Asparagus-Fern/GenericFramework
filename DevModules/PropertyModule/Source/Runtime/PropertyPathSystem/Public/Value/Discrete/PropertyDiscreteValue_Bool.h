// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Bool.generated.h"

/**
 * Bool类型属性
 */
UCLASS(MinimalAPI)
class UPropertyDiscreteValue_Bool : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	UPropertyDiscreteValue_Bool();

public:
	PROPERTYPATHSYSTEM_API bool GetDefaultBoolValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultBoolValue(bool InValue);

	PROPERTYPATHSYSTEM_API void SetTrueText(const FText& InText);
	PROPERTYPATHSYSTEM_API void SetFalseText(const FText& InText);
};
