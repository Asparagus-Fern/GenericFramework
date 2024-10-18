// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ListEntry/PropertyListEntry_Discrete.h"

#include "Components/PanelWidget.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic.h"

void UPropertyListEntry_Discrete::SetPropertyEntity(UPropertyEntity* InProperty)
{
	DiscreteProperty = Cast<UPropertyDiscreteValueDynamic>(InProperty);
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