// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyValueBase.h"
#include "PropertyDiscreteValueBase.generated.h"

class UMultiPropertyValueViewModel;
class USinglePropertyValueViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyDiscreteValueBase : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitViewModelProperty() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

private:
	void HandleOnPropertyValueAdded(USinglePropertyValueViewModel* ViewModel);
	void HandleOnPropertyValueRemoved(USinglePropertyValueViewModel* ViewModel);

	FDelegateHandle OnSelectedValueIndexChangedHandle;
	void HandleOnSelectedValueIndexChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueAdded(USinglePropertyValueViewModel* ViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueRemoved(USinglePropertyValueViewModel* ViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnSelectedValueIndexChanged(USinglePropertyValueViewModel* ViewModel);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMultiPropertyValueViewModel> MultiPropertyValueViewModel = nullptr;
};
