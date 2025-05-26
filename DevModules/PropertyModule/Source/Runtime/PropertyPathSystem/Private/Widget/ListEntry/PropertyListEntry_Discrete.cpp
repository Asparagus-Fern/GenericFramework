// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Widget/ListEntry/PropertyListEntry_Discrete.h"

#include "Components/PanelWidget.h"
#include "Value/Discrete/PropertyDiscreteValue.h"

void UPropertyListEntry_Discrete::SetPropertyEntity(UPropertyEntity* InProperty)
{
	DiscreteProperty = Cast<UPropertyDiscreteValue>(InProperty);
	check(DiscreteProperty);

	Super::SetPropertyEntity(InProperty);
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
	Panel_Value->SetIsEnabled(bLocalIsEnabled);
}