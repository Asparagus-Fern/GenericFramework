// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertySingleValueBase.h"
#include "PropertyActionValueBase.generated.h"

class UActionPropertyValueViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyActionValueBase : public UPropertySingleValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitViewModelProperty() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UActionPropertyValueViewModel> ActionPropertyValueViewModel = nullptr;
};
