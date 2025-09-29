// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyValueBase.h"
#include "PropertyActionValueBase.generated.h"

class UActionPropertyValueViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyActionValueBase : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UActionPropertyValueViewModel> ActionPropertyValueViewModel = nullptr;
};
