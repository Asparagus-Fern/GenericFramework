// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyValueViewModel.h"
#include "SinglePropertyValueViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API USinglePropertyValueViewModel : public UPropertyValueViewModel
{
	GENERATED_BODY()

public:
	virtual void InitializeWithProperty(FName InPropertyName, const FProperty* InProperty);

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FName PropertyValueName = NAME_None;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText PropertyValueDisplayName;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText PropertyValueTooltip;
};
