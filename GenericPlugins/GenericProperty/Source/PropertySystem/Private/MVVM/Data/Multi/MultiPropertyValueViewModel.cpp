// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/Data/Multi/MultiPropertyValueViewModel.h"

bool UMultiPropertyValueViewModel::Initialize(UPropertyProxy* InOwnerProxy)
{
	bool Result = Super::Initialize(InOwnerProxy);

	if (Result)
	{
		for (auto& PropertyValue : PropertyValues)
		{
			PropertyValue.Value->Initialize(GetOwnerProxy());
		}
	}

	return Result;
}

void UMultiPropertyValueViewModel::Deinitialize()
{
	Super::Deinitialize();
}

FString UMultiPropertyValueViewModel::GetInitialValueAsString()
{
	return GetInitialValue();
}

void UMultiPropertyValueViewModel::SetInitialValueFromString(const FString& InValue)
{
	SetInitialValue(InValue);
}

FString UMultiPropertyValueViewModel::GetCurrentValueAsString()
{
	return GetSelectedValue();
}

void UMultiPropertyValueViewModel::SetCurrentValueFromString(const FString& InValue)
{
	SetSelectedValue(InValue);
}

void UMultiPropertyValueViewModel::AddValuesByName(const TMap<FString, FText>& InDisplayNames)
{
	for (auto& DisplayName : InDisplayNames)
	{
		AddValueByName(DisplayName.Key, DisplayName.Value);
	}
}

void UMultiPropertyValueViewModel::AddValues(const TMap<FString, UPropertyViewModel*>& InViewModels)
{
	for (const auto& InViewModel : InViewModels)
	{
		AddValue(InViewModel.Key, InViewModel.Value);
	}
}

void UMultiPropertyValueViewModel::AddValueByName(FString InName, const FText& InDisplayName)
{
	UPropertyViewModel* NewViewModel = NewObject<UPropertyViewModel>(this);
	NewViewModel->PropertyName = FName(TEXT("GenerateChildProperty"));
	NewViewModel->PropertyDisplayName = InDisplayName;
	AddValue(InName, NewViewModel);
}

void UMultiPropertyValueViewModel::AddValue(FString InName, UPropertyViewModel* InViewModel)
{
	check(InViewModel)

	auto OnValueChanged = [this](FString InName, UPropertyViewModel* InViewModel)
	{
		PropertyValues.Emplace(InName, InViewModel);
		OnPropertyValueAddedEvent.Broadcast(InName, InViewModel);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyValues);
	};

	if (!PropertyValues.Contains(InName))
	{
		OnValueChanged(InName, InViewModel);
	}
	else
	{
		UPropertyViewModel* ViewModel = PropertyValues.FindRef(InName);
		if (ViewModel != InViewModel)
		{
			OnValueChanged(InName, InViewModel);
		}
	}
}

void UMultiPropertyValueViewModel::RemoveValue(UPropertyViewModel* InViewModel)
{
	ensure(InViewModel);

	FString Name;
	if (FindViewModelName(InViewModel, Name))
	{
		RemoveValueByName(Name);
	}
}

void UMultiPropertyValueViewModel::RemoveValueByName(FString InName)
{
	if (PropertyValues.Contains(InName))
	{
		UPropertyViewModel* RemovedViewModel = PropertyValues.FindAndRemoveChecked(InName);
		OnPropertyValueRemovedEvent.Broadcast(InName, RemovedViewModel);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyValues);
	}
}

bool UMultiPropertyValueViewModel::FindViewModel(const FString& InName, UPropertyViewModel*& OutViewModel) const
{
	if (PropertyValues.Contains(InName))
	{
		OutViewModel = PropertyValues.FindRef(InName);
		return true;
	}

	return false;
}

bool UMultiPropertyValueViewModel::FindViewModelName(UPropertyViewModel* InViewModel, FString& OutName) const
{
	if (const FString* Result = PropertyValues.FindKey(InViewModel))
	{
		OutName = *Result;
	}

	return false;
}

int32 UMultiPropertyValueViewModel::GetInitialValueIndex() const
{
	TArray<FString> KeyNames;
	PropertyValues.GenerateKeyArray(KeyNames);
	return KeyNames.Find(InitialValue);
}

void UMultiPropertyValueViewModel::SetInitialValueByIndex(int32 InIndex)
{
	TArray<FString> KeyNames;
	PropertyValues.GenerateKeyArray(KeyNames);

	if (KeyNames.IsValidIndex(InIndex))
	{
		SetInitialValue(KeyNames[InIndex]);
	}
}

FString UMultiPropertyValueViewModel::GetInitialValue() const
{
	return InitialValue;
}

void UMultiPropertyValueViewModel::SetInitialValue(FString InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(InitialValue, InValue);
}

int32 UMultiPropertyValueViewModel::GetSelectedValueIndex() const
{
	TArray<FString> KeyNames;
	PropertyValues.GenerateKeyArray(KeyNames);
	return KeyNames.Find(SelectedValue);
}

void UMultiPropertyValueViewModel::SetSelectedValueByIndex(int32 InIndex)
{
	TArray<FString> KeyNames;
	PropertyValues.GenerateKeyArray(KeyNames);

	if (KeyNames.IsValidIndex(InIndex))
	{
		SetSelectedValue(KeyNames[InIndex]);
	}
}

FString UMultiPropertyValueViewModel::GetSelectedValue() const
{
	return SelectedValue;
}

void UMultiPropertyValueViewModel::SetSelectedValue(FString InValue)
{
	if (SelectedValue != InValue)
	{
		PrePropertyChanged();
		SelectedValue = InValue;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(SelectedValue);
		PostPropertyChanged();
	}
}
