// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ListEntry/Scalar/PropertyListEntry_ScalarSlider.h"

#include "Base/PropertyEditCondition.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Value/Scalar/PropertyScalarValueDynamic.h"

void UPropertyListEntry_ScalarSlider::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_PropertyValue->OnValueChanged.AddDynamic(this, &UPropertyListEntry_ScalarSlider::HandleSliderValueChanged);
	Slider_PropertyValue->OnMouseCaptureEnd.AddDynamic(this, &UPropertyListEntry_ScalarSlider::HandleSliderCaptureEnded);
	Slider_PropertyValue->OnControllerCaptureEnd.AddDynamic(this, &UPropertyListEntry_ScalarSlider::HandleSliderCaptureEnded);
}

void UPropertyListEntry_ScalarSlider::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	Slider_PropertyValue->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_ScalarSlider::Refresh()
{
	const float Value = ScalarProperty->GetValueNormalized();

	Slider_PropertyValue->SetValue(Value);
	Slider_PropertyValue->SetStepSize(ScalarProperty->GetNormalizedStepSize());

	Super::Refresh();
}

void UPropertyListEntry_ScalarSlider::HandleSliderValueChanged(float Value)
{
	TGuardValue<bool> Suspend(bSuspendChangeUpdates, true);

	ScalarProperty->SetValueNormalized(Value);
	Value = ScalarProperty->GetValueNormalized();

	Slider_PropertyValue->SetValue(Value);

	if (Text_PropertyValue)
	{
		Text_PropertyValue->SetText(ScalarProperty->GetFormattedText());
	}
	
	OnValueChanged(Value);
}

void UPropertyListEntry_ScalarSlider::HandleSliderCaptureEnded()
{
	TGuardValue<bool> Suspend(bSuspendChangeUpdates, true);
}
