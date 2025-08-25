// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "MVVM/PropertyValueViewModel.h"
#include "PropertyValueBase.generated.h"

class UPropertyValueSpawner;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyValueBase : public UGenericWidget
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintPure, DisplayName="GetViewModel", meta=(DeterminesOutputType = "InClass"))
	PROPERTYSYSTEM_API UPropertyValueViewModel* BP_GetViewModel(TSubclassOf<UPropertyValueViewModel> InClass);

	UFUNCTION(BlueprintCallable, DisplayName="SetViewModel")
	PROPERTYSYSTEM_API void BP_SetViewModel(UPropertyValueViewModel* InViewModel);

public:
	template <typename T = UPropertyValueViewModel>
	T* GetViewModel()
	{
		return IsValid(PropertyValueViewModel) ? Cast<T>(PropertyValueViewModel) : nullptr;
	}

	PROPERTYSYSTEM_API void SetViewModel(UPropertyValueViewModel* InViewModel)
	{
		check(InViewModel);
		PropertyValueViewModel = InViewModel;
		PostInitViewModelProperty();
		NativeOnViewModelInitialized();
		OnViewModelInitialized();
	}

protected:
	friend UPropertyValueSpawner;

	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportViewModelClass() PURE_VIRTUAL(, return nullptr;)

	PROPERTYSYSTEM_API virtual void PostInitViewModelProperty() { return; }

	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized();
	UFUNCTION(BlueprintImplementableEvent)
	PROPERTYSYSTEM_API void OnViewModelInitialized();

	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized();
	UFUNCTION(BlueprintImplementableEvent)
	PROPERTYSYSTEM_API void OnViewModelDeinitialized();

protected:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"))
	TObjectPtr<UPropertyValueViewModel> PropertyValueViewModel = nullptr;
};
