// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ListEntry/PropertyListEntry_Discrete.h"

#include "CommonRotator.h"
#include "Value/Discrete/PropertyDiscreteValue.h"

void UPropertyListEntry_Discrete::SetPropertyEntity(UPropertyEntity* InProperty)
{
	DiscreteProperty = Cast<UPropertyDiscreteValue>(InProperty);
	check(DiscreteProperty);

	Super::SetPropertyEntity(InProperty);
}

void UPropertyListEntry_Discrete::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Rotator_PropertyValue->OnRotatedEvent.AddUObject(this, &UPropertyListEntry_Discrete::HandleRotatorChangedValue);
	Button_Increase->OnClicked().AddUObject(this, &UPropertyListEntry_Discrete::HandleOptionIncrease);
	Button_Decrease->OnClicked().AddUObject(this, &UPropertyListEntry_Discrete::HandleOptionDecrease);
}

void UPropertyListEntry_Discrete::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();
	DiscreteProperty = nullptr;
}

void UPropertyListEntry_Discrete::OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson)
{
	Super::OnPropertyChanged(InProperty, Reson);
	Refresh();
}

void UPropertyListEntry_Discrete::OnPropertyEditConditionChanged(UPropertyEntity* InProperty)
{
	Super::OnPropertyEditConditionChanged(InProperty);
	Refresh();
}

void UPropertyListEntry_Discrete::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	Button_Decrease->SetIsEnabled(bLocalIsEnabled);
	Rotator_PropertyValue->SetIsEnabled(bLocalIsEnabled);
	Button_Increase->SetIsEnabled(bLocalIsEnabled);
	Panel_Value->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_Discrete::HandleRotatorChangedValue(int32 Value, bool bUserInitiated)
{
	if (bUserInitiated)
	{
		DiscreteProperty->SetDiscreteOptionByIndex(Value);
	}
}

void UPropertyListEntry_Discrete::HandleOptionIncrease()
{
	Rotator_PropertyValue->ShiftTextRight();
	DiscreteProperty->SetDiscreteOptionByIndex(Rotator_PropertyValue->GetSelectedIndex());
}

void UPropertyListEntry_Discrete::HandleOptionDecrease()
{
	Rotator_PropertyValue->ShiftTextLeft();
	DiscreteProperty->SetDiscreteOptionByIndex(Rotator_PropertyValue->GetSelectedIndex());
}

void UPropertyListEntry_Discrete::Refresh()
{
	const TArray<FText> Options = DiscreteProperty->GetDiscreteOptions();
	ensure(Options.Num() > 0);

	Rotator_PropertyValue->PopulateTextLabels(Options);
	Rotator_PropertyValue->SetSelectedItem(DiscreteProperty->GetDiscreteOptionIndex());
}