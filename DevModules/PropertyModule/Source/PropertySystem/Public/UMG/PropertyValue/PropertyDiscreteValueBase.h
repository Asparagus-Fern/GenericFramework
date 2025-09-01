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
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

private:
	void HandleOnPropertyValueAdded(USinglePropertyValueViewModel* ViewModel);
	void HandleOnPropertyValueRemoved(USinglePropertyValueViewModel* ViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnAllowWrapChanged(bool IsAllowWrap);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueAdded(USinglePropertyValueViewModel* ViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueRemoved(USinglePropertyValueViewModel* ViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnSelectedValueIndexChanged(int32 SelectedValueIndex);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMultiPropertyValueViewModel> MultiPropertyValueViewModel = nullptr;
};
