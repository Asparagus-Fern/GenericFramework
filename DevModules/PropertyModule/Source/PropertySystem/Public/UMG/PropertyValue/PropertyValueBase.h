// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "MVVM/PropertyViewModel.h"
#include "PropertyValueBase.generated.h"

class UPropertyValueSpawner;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyValueBase : public UGenericWidget
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintPure, DisplayName="GetPropertyViewModel", meta=(DeterminesOutputType = "InClass"))
	PROPERTYSYSTEM_API UPropertyViewModel* BP_GetPropertyViewModel(TSubclassOf<UPropertyViewModel> InClass);

	UFUNCTION(BlueprintCallable, DisplayName="SetPropertyViewModel")
	PROPERTYSYSTEM_API void BP_SetPropertyViewModel(UPropertyViewModel* InViewModel);

public:
	template <typename T = UPropertyViewModel>
	T* GetPropertyViewModel()
	{
		return IsValid(PropertyViewModel) ? Cast<T>(PropertyViewModel) : nullptr;
	}

	PROPERTYSYSTEM_API void SetPropertyViewModel(UPropertyViewModel* InViewModel)
	{
		check(InViewModel);

		PreInitPropertyViewModel();
		PropertyViewModel = InViewModel;
		PostInitPropertyViewModel();

		NativeOnViewModelInitialized();
		OnViewModelInitialized();
	}

protected:
	friend UPropertyValueSpawner;

	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyViewModel> GetSupportPropertyViewModelClass();

	PROPERTYSYSTEM_API virtual void PreInitPropertyViewModel();
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel();

	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized();
	UFUNCTION(BlueprintImplementableEvent)
	PROPERTYSYSTEM_API void OnViewModelInitialized();

	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized();
	UFUNCTION(BlueprintImplementableEvent)
	PROPERTYSYSTEM_API void OnViewModelDeinitialized();

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnIsAutoApplyPropertyChanged(bool InIsAutoApplyProperty);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnIsDirtyProxyChanged(bool InIsDirtyProxy);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyNameChanged(FName InPropertyName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyDisplayNameChanged(const FText& InPropertyDisplayName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyDescriptionChanged(const FText& InPropertyDescription);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"))
	TObjectPtr<UPropertyViewModel> PropertyViewModel = nullptr;
};
