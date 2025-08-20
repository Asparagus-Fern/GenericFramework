// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "DiscreteValueViewModel.generated.h"


/**
 * 
 */
UCLASS(MinimalAPI)
class UDiscreteValueViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API void InitializeWithProperty(const FProperty* InProperty);

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FName ValueName = NAME_None;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText ValueDisplayName;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText ValueTooltip;
};
