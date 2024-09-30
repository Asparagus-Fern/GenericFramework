// Fill out your copyright notice in the Description page of Project Settings.


#include "ListEntry/PropertyListEntry_Scalar.h"

#include "Components/PanelWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Value/Scalar/PropertyScalarValue.h"

void UPropertyListEntry_Scalar::SetPropertyEntity(UPropertyEntity* InProperty)
{
	ScalarProperty = Cast<UPropertyScalarValue>(InProperty);
	check(ScalarProperty);

	Super::SetPropertyEntity(InProperty);

	Refresh();
}

void UPropertyListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_PropertyValue->OnValueChanged.AddDynamic(this, &UPropertyListEntry_Scalar::HandleSliderValueChanged);
	Slider_PropertyValue->OnMouseCaptureEnd.AddDynamic(this, &UPropertyListEntry_Scalar::HandleSliderCaptureEnded);
	Slider_PropertyValue->OnControllerCaptureEnd.AddDynamic(this, &UPropertyListEntry_Scalar::HandleSliderCaptureEnded);
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
	Slider_PropertyValue->SetIsEnabled(bLocalIsEnabled);
	Panel_Value->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_Scalar::HandleSliderValueChanged(float Value)
{
	TGuardValue<bool> Suspend(bSuspendChangeUpdates, true);

	ScalarProperty->SetValueNormalized(Value);
	Value = ScalarProperty->GetValueNormalized();

	Slider_PropertyValue->SetValue(Value);
	Text_PropertyValue->SetText(ScalarProperty->GetFormattedText());

	OnValueChanged(Value);
}

void UPropertyListEntry_Scalar::HandleSliderCaptureEnded()
{
	TGuardValue<bool> Suspend(bSuspendChangeUpdates, true);
}

void UPropertyListEntry_Scalar::Refresh()
{
	const float Value = ScalarProperty->GetValueNormalized();

	Slider_PropertyValue->SetValue(Value);
	Slider_PropertyValue->SetStepSize(ScalarProperty->GetNormalizedStepSize());
	Text_PropertyValue->SetText(ScalarProperty->GetFormattedText());

	TOptional<double> DefaultValue = ScalarProperty->GetDefaultValueNormalized();
	OnDefaultValueChanged(DefaultValue.IsSet() ? DefaultValue.GetValue() : -1.0);

	OnValueChanged(Value);
}
