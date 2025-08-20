// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/DiscreteValuesViewModel.h"

#include "MVVM/DiscreteValueViewModel.h"

void UDiscreteValuesViewModel::AddValue(const FName InValueName, FText InValueDisplayName, const int32 Index)
{
	check(InValueName != NAME_None)

	UDiscreteValueViewModel* NewValue = NewObject<UDiscreteValueViewModel>(this);
	NewValue->ValueName = InValueName;
	NewValue->ValueDisplayName = InValueDisplayName;

	if (Index >= 0)
	{
		Values.EmplaceAt(Index, NewValue);
	}
	else
	{
		Values.Emplace(NewValue);
	}

	OnDiscreteValueAddedEvent.Broadcast(NewValue);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Values);
}

void UDiscreteValuesViewModel::AddValueWithProperty(const FProperty* InProperty, int32 Index)
{
	check(InProperty);

	UDiscreteValueViewModel* NewValue = NewObject<UDiscreteValueViewModel>(this);
	NewValue->InitializeWithProperty(InProperty);

	if (Index >= 0)
	{
		Values.EmplaceAt(Index, NewValue);
	}
	else
	{
		Values.Emplace(NewValue);
	}

	OnDiscreteValueAddedEvent.Broadcast(NewValue);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Values);
}

void UDiscreteValuesViewModel::RemoveValue(const FName InValueName)
{
	check(InValueName != NAME_None)

	TArray<TObjectPtr<UDiscreteValueViewModel>> TempValues = Values;

	for (auto& Value : TempValues)
	{
		if (Value->ValueName == InValueName)
		{
			Values.Remove(Value);
			OnDiscreteValueRemovedEvent.Broadcast(Value);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Values);
		}
	}
}

void UDiscreteValuesViewModel::RemoveValueWithProperty(const FProperty* InProperty)
{
	check(InProperty);

	TArray<TObjectPtr<UDiscreteValueViewModel>> TempValues = Values;

	for (auto& Value : TempValues)
	{
		if (Value->ValueName == InProperty->GetFName())
		{
			Values.Remove(Value);
			OnDiscreteValueRemovedEvent.Broadcast(Value);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Values);
		}
	}
}

UDiscreteValueViewModel* UDiscreteValuesViewModel::GetCurrentValue()
{
	return Values.IsValidIndex(CurrentValueIndex) ? Values[CurrentValueIndex] : nullptr;
}

UDiscreteValueViewModel* UDiscreteValuesViewModel::GetDefaultValue()
{
	return Values.IsValidIndex(DefaultValueIndex) ? Values[DefaultValueIndex] : nullptr;
}

void UDiscreteValuesViewModel::SetValueByIndex(int32 InValueIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(CurrentValueIndex, InValueIndex);
}

void UDiscreteValuesViewModel::SetValueByName(FName InValueName)
{
	check(InValueName != NAME_None)

	for (int32 It = 0; It < Values.Num(); It++)
	{
		if (Values[It]->ValueName == InValueName)
		{
			CurrentValueIndex = It;
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CurrentValueIndex);
		}
	}
}

void UDiscreteValuesViewModel::SetValueByItem(UDiscreteValueViewModel* InValue)
{
	SetValueByName(InValue->ValueName);
}
