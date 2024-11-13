// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ListEntry/PropertyListEntry_Scalar.h"

#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Value/Scalar/PropertyScalarValueDynamic.h"

void UPropertyListEntry_Scalar::SetPropertyEntity(UPropertyEntity* InProperty)
{
	ScalarProperty = Cast<UPropertyScalarValueDynamic>(InProperty);
	check(ScalarProperty);

	Super::SetPropertyEntity(InProperty);

	Refresh();
}

void UPropertyListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPropertyListEntry_Scalar::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();
	ScalarProperty = nullptr;
}

void UPropertyListEntry_Scalar::OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson)
{
	Super::OnPropertyChanged(InProperty, Reson);
	Refresh();
}

void UPropertyListEntry_Scalar::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	Panel_Value->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_Scalar::Refresh()
{
	if (Text_PropertyValue)
	{
		Text_PropertyValue->SetText(ScalarProperty->GetFormattedText());
	}

	TOptional<double> DefaultValue = ScalarProperty->GetDefaultValueNormalized();
	OnDefaultValueChanged(DefaultValue.IsSet() ? DefaultValue.GetValue() : -1.0);

	const float Value = ScalarProperty->GetValueNormalized();
	OnValueChanged(Value);
}
