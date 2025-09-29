// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonWidget.h"
#include "PropertyListItemOption.generated.h"

class UPropertyViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyListItemOption : public UGenericButtonWidget
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyViewModel(UPropertyViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyViewModelInitialized(UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyApply(UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyReset(UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyValueChanged(UPropertyViewModel* InViewModel, EPropertyChangedReason ChangedReason);

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UPropertyViewModel> PropertyViewModel = nullptr;
};
