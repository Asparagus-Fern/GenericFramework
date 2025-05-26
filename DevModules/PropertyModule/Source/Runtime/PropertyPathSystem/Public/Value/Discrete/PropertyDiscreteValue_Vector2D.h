// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Vector2D.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Vector2D : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	FVector2D GetVector2DValue() const;
	void SetVector2DValue(const FVector2D& InValue);

	FVector2D GetDefaultVector2DValue() const;
	void SetDefaultVector2DValue(const FVector2D& InValue);
};
