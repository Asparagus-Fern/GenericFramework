// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyValueViewModel.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"
#include "MultiPropertyValueViewModel.generated.h"

class USinglePropertyValueViewModel;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyValueAdded, USinglePropertyValueViewModel*);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyValueRemoved, USinglePropertyValueViewModel*);

typedef TDelegate<int32()> FMultiPropertyValueGetter;
typedef TDelegate<void(int32)> FMultiPropertyValueSetter;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMultiPropertyValueViewModel : public UPropertyValueViewModel
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void Initialize_Implementation() override;
	PROPERTYSYSTEM_API virtual void Deinitialize_Implementation() override;
	PROPERTYSYSTEM_API virtual void Apply_Implementation() override;
	PROPERTYSYSTEM_API virtual void Reverse_Implementation() override;
	PROPERTYSYSTEM_API virtual void Reset_Implementation() override;

public:
	template <typename T = USinglePropertyValueViewModel>
	T* AddValue(const int32 Index = -1)
	{
		USinglePropertyValueViewModel* NewViewModel = NewObject<USinglePropertyValueViewModel>(this, T::StaticClass());
		AddValue(NewViewModel, Index);
		return Cast<T>(NewViewModel);
	}

	template <typename T = USinglePropertyValueViewModel>
	T* AddValue(FName InPropertyName, const FProperty* InProperty, const int32 Index = -1)
	{
		USinglePropertyValueViewModel* NewViewModel = NewObject<USinglePropertyValueViewModel>(this, T::StaticClass());
		NewViewModel->InitializeWithProperty(InPropertyName, InProperty);

		AddValue(NewViewModel, Index);
		return Cast<T>(NewViewModel);
	}

	PROPERTYSYSTEM_API void AddValue(USinglePropertyValueViewModel* InViewModel, int32 Index = -1);

	PROPERTYSYSTEM_API void RemoveValue(FName InValueName);
	PROPERTYSYSTEM_API void RemoveValue(USinglePropertyValueViewModel* InViewModel);

	PROPERTYSYSTEM_API USinglePropertyValueViewModel* FindViewModel(FName InValueName);
	PROPERTYSYSTEM_API int32 FindViewModelIndex(FName InValueName);
	PROPERTYSYSTEM_API int32 FindViewModelIndex(USinglePropertyValueViewModel* InValue);

	PROPERTYSYSTEM_API USinglePropertyValueViewModel* GetDefaultValue();
	PROPERTYSYSTEM_API USinglePropertyValueViewModel* GetSelectedValue();

	PROPERTYSYSTEM_API void SetDefaultValue(USinglePropertyValueViewModel* InValue);
	PROPERTYSYSTEM_API void SetDefaultValue(FName InValueName);
	PROPERTYSYSTEM_API void SetDefaultValue(int32 InValueIndex);

	PROPERTYSYSTEM_API void SetSelectedValue(USinglePropertyValueViewModel* InValue);
	PROPERTYSYSTEM_API void SetSelectedValue(FName InValueName);
	PROPERTYSYSTEM_API void SetSelectedValue(int32 InValueIndex);

	PROPERTYSYSTEM_API FMultiPropertyValueGetter& GetPropertyGetter() { return PropertyValueGetter; }
	PROPERTYSYSTEM_API void SetPropertyValueGetter(const FMultiPropertyValueGetter& InPropertyValueGetter) { PropertyValueGetter = InPropertyValueGetter; }
	PROPERTYSYSTEM_API FMultiPropertyValueSetter& GetPropertySetter() { return PropertyValueSetter; }
	PROPERTYSYSTEM_API void SetPropertyValueSetter(const FMultiPropertyValueSetter& InPropertyValueSetter) { PropertyValueSetter = InPropertyValueSetter; }

public:
	FOnPropertyValueAdded OnPropertyValueAddedEvent;
	FOnPropertyValueRemoved OnPropertyValueRemovedEvent;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 DefaultValueIndex = 0;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 SelectedValueIndex = 0;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<TObjectPtr<USinglePropertyValueViewModel>> PropertyValues;

private:
	int32 CacheSelectedValueIndex = SelectedValueIndex;
	FMultiPropertyValueGetter PropertyValueGetter;
	FMultiPropertyValueSetter PropertyValueSetter;
};
