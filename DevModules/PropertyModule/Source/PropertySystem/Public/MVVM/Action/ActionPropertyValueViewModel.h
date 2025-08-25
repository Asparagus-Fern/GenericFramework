// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"
#include "ActionPropertyValueViewModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPropertyActionValueExecute);

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UActionPropertyValueViewModel : public USinglePropertyValueViewModel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPropertyActionValueExecute OnPropertyActionValueExecute;
};
