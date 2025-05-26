// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Widget/ListEntry/Discrete/PropertyListEntry_DiscreteRotator.h"
#include "CommonRotator.h"

#include "CommonButtonBase.h"
#include "Base/PropertyEditCondition.h"
#include "Value/Discrete/PropertyDiscreteValue.h"

void UPropertyListEntry_DiscreteRotator::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Rotator_PropertyValue->OnRotatedEvent.AddUObject(this, &UPropertyListEntry_DiscreteRotator::HandleRotatorChangedValue);
	Button_Increase->OnClicked().AddUObject(this, &UPropertyListEntry_DiscreteRotator::HandleOptionIncrease);
	Button_Decrease->OnClicked().AddUObject(this, &UPropertyListEntry_DiscreteRotator::HandleOptionDecrease);
}

void UPropertyListEntry_DiscreteRotator::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();

	Rotator_PropertyValue->SetIsEnabled(bLocalIsEnabled);
	Button_Increase->SetIsEnabled(bLocalIsEnabled);
	Button_Decrease->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_DiscreteRotator::HandleRotatorChangedValue(int32 Value, bool bUserInitiated)
{
	if (bUserInitiated)
	{
		DiscreteProperty->SetDiscreteOptionByIndex(Value);
	}
}

void UPropertyListEntry_DiscreteRotator::HandleOptionIncrease()
{
	Rotator_PropertyValue->ShiftTextRight();
	DiscreteProperty->SetDiscreteOptionByIndex(Rotator_PropertyValue->GetSelectedIndex());
}

void UPropertyListEntry_DiscreteRotator::HandleOptionDecrease()
{
	Rotator_PropertyValue->ShiftTextLeft();
	DiscreteProperty->SetDiscreteOptionByIndex(Rotator_PropertyValue->GetSelectedIndex());
}

void UPropertyListEntry_DiscreteRotator::Refresh()
{
	const TArray<FText> Options = DiscreteProperty->GetAllOptionText();
	ensure(Options.Num() > 0);

	Rotator_PropertyValue->PopulateTextLabels(Options);
	Rotator_PropertyValue->SetSelectedItem(DiscreteProperty->GetDiscreteOptionIndex());
}
