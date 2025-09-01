// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyValueBase.h"
#include "PropertySingleValueBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertySingleValueBase : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueNameChanged(FName InName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueDisplayNameChanged(const FText& InDisplayName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueTooltipChanged(const FText& InTooltip);
};
