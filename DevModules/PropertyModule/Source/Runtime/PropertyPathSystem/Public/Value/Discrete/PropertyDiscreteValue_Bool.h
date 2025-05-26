// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Bool.generated.h"

/**
 * Bool类型属性
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Bool : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	UPropertyDiscreteValue_Bool();

public:
	bool GetDefaultBoolValue() const;
	void SetDefaultBoolValue(bool InValue);

	void SetTrueText(const FText& InText);
	void SetFalseText(const FText& InText);
};
