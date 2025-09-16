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
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

private:
	void HandleOnPropertyValueAdded(const FString& InName, UPropertyViewModel* InViewModel);
	void HandleOnPropertyValueRemoved(const FString& InName, UPropertyViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnAllowWrapChanged(bool IsAllowWrap);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueAdded(const FString& InName, UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueRemoved(const FString& InName, UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnSelectedValueChanged(const FString& InSelectedValue);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMultiPropertyValueViewModel> MultiPropertyValueViewModel = nullptr;
};
