// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/Multi/MultiPropertyValueViewModel.h"

#include "MVVM/Single/SinglePropertyValueViewModel.h"

void UMultiPropertyValueViewModel::Initialize_Implementation()
{
	Super::Initialize_Implementation();

	SetDefaultValue(GetPropertyGetter().IsBound() ? GetPropertyGetter().Execute() : 0);
	SetSelectedValue(GetPropertyGetter().IsBound() ? GetPropertyGetter().Execute() : 0);
}

void UMultiPropertyValueViewModel::Deinitialize_Implementation()
{
	Super::Deinitialize_Implementation();
}

void UMultiPropertyValueViewModel::Apply_Implementation()
{
	Super::Apply_Implementation();

	SetDefaultValue(SelectedValueIndex);
	GetPropertySetter().ExecuteIfBound(SelectedValueIndex);
}

void UMultiPropertyValueViewModel::Reverse_Implementation()
{
	Super::Reverse_Implementation();

	SetSelectedValue(CacheSelectedValueIndex);
}

void UMultiPropertyValueViewModel::Reset_Implementation()
{
	Super::Reset_Implementation();

	SetSelectedValue(DefaultValueIndex);
	CacheSelectedValueIndex = SelectedValueIndex;
}

void UMultiPropertyValueViewModel::AddValue(USinglePropertyValueViewModel* InViewModel, const int32 Index)
{
	check(InViewModel)

	if (Index >= 0)
	{
		PropertyValues.EmplaceAt(Index, InViewModel);
	}
	else
	{
		PropertyValues.Emplace(InViewModel);
	}

	OnPropertyValueAddedEvent.Broadcast(InViewModel);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyValues);
}

void UMultiPropertyValueViewModel::RemoveValue(FName InValueName)
{
	check(InValueName != NAME_None)

	if (USinglePropertyValueViewModel* ViewModel = FindViewModel(InValueName))
	{
		RemoveValue(ViewModel);
	}
}

void UMultiPropertyValueViewModel::RemoveValue(USinglePropertyValueViewModel* InViewModel)
{
	check(InViewModel)

	if (PropertyValues.Contains(InViewModel))
	{
		PropertyValues.Remove(InViewModel);
		OnPropertyValueRemovedEvent.Broadcast(InViewModel);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyValues);
	}
}

USinglePropertyValueViewModel* UMultiPropertyValueViewModel::FindViewModel(FName InValueName)
{
	for (auto& Value : PropertyValues)
	{
		if (Value->PropertyValueName == InValueName)
		{
			return Value;
		}
	}

	return nullptr;
}

int32 UMultiPropertyValueViewModel::FindViewModelIndex(FName InValueName)
{
	return PropertyValues.Find(FindViewModel(InValueName));
}

int32 UMultiPropertyValueViewModel::FindViewModelIndex(USinglePropertyValueViewModel* InValue)
{
	return PropertyValues.Find(InValue);
}

USinglePropertyValueViewModel* UMultiPropertyValueViewModel::GetDefaultValue()
{
	return PropertyValues.IsValidIndex(DefaultValueIndex) ? PropertyValues[DefaultValueIndex] : nullptr;
}

USinglePropertyValueViewModel* UMultiPropertyValueViewModel::GetSelectedValue()
{
	return PropertyValues.IsValidIndex(SelectedValueIndex) ? PropertyValues[SelectedValueIndex] : nullptr;
}

void UMultiPropertyValueViewModel::SetDefaultValue(USinglePropertyValueViewModel* InValue)
{
	SetDefaultValue(FindViewModelIndex(InValue));
}

void UMultiPropertyValueViewModel::SetDefaultValue(FName InValueName)
{
	SetDefaultValue(FindViewModelIndex(InValueName));
}

void UMultiPropertyValueViewModel::SetDefaultValue(int32 InValueIndex)
{
	check(InValueIndex != INDEX_NONE && PropertyValues.IsValidIndex(InValueIndex))
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(DefaultValueIndex, InValueIndex);
}

void UMultiPropertyValueViewModel::SetSelectedValue(USinglePropertyValueViewModel* InValue)
{
	SetSelectedValue(FindViewModelIndex(InValue));
}

void UMultiPropertyValueViewModel::SetSelectedValue(FName InValueName)
{
	SetSelectedValue(FindViewModelIndex(InValueName));
}

void UMultiPropertyValueViewModel::SetSelectedValue(int32 InValueIndex)
{
	check(InValueIndex != INDEX_NONE && PropertyValues.IsValidIndex(InValueIndex))

	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(SelectedValueIndex, InValueIndex))
	{
		MarkAsPropertyDirty();
	}
}
