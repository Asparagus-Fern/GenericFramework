// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyValueViewModel.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"
#include "MultiPropertyValueViewModel.generated.h"

class USinglePropertyValueViewModel;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyValueAdded, USinglePropertyValueViewModel*);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropertyValueRemoved, USinglePropertyValueViewModel*);

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UMultiPropertyValueViewModel : public UPropertyValueViewModel
{
	GENERATED_BODY()

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

	void AddValue(USinglePropertyValueViewModel* InViewModel, int32 Index = -1);

	void RemoveValue(FName InValueName);
	void RemoveValue(USinglePropertyValueViewModel* InViewModel);

	USinglePropertyValueViewModel* FindViewModel(FName InValueName);
	int32 FindViewModelIndex(FName InValueName);
	int32 FindViewModelIndex(USinglePropertyValueViewModel* InValue);

	USinglePropertyValueViewModel* GetDefaultValue();
	USinglePropertyValueViewModel* GetSelectedValue();

	void SetSelectedValue(USinglePropertyValueViewModel* InValue);
	void SetSelectedValue(FName InValueName);
	void SetSelectedValue(int32 InValueIndex);

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
};
