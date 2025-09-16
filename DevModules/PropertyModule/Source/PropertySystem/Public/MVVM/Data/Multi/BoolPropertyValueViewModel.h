// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MultiPropertyValueViewModel.h"
#include "BoolPropertyValueViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UBoolPropertyValueViewModel : public UMultiPropertyValueViewModel
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetTrueText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetFalseText(const FText& InText);
};
