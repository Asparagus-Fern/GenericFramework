// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Vector2D.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyDiscreteValue_Vector2D : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API FVector2D GetVector2DValue() const;
	PROPERTYPATHSYSTEM_API void SetVector2DValue(const FVector2D& InValue);

	PROPERTYPATHSYSTEM_API FVector2D GetDefaultVector2DValue() const;
	PROPERTYPATHSYSTEM_API void SetDefaultVector2DValue(const FVector2D& InValue);
};
