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
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitViewModelProperty() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

private:
	FDelegateHandle OnPropertyValueNameChangedHandle;
	virtual void HandleOnPropertyValueNameChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

	FDelegateHandle OnPropertyValueDisplayNameChangedHandle;
	virtual void HandleOnPropertyValueDisplayNameChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

	FDelegateHandle OnPropertyValueTooltipChangedHandle;
	virtual void HandleOnPropertyValueTooltipChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueNameChanged(FName InName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueDisplayNameChanged(const FText& InDisplayName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueTooltipChanged(const FText& InTooltip);
};
