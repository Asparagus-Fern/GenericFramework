// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/Value/ScalarValue_SpinBox.h"

#include "Components/SpinBox.h"
#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"

void UScalarValue_SpinBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (SpinBox_PropertyValue)
	{
		SpinBox_PropertyValue->OnValueChanged.AddUniqueDynamic(this, &ThisClass::HandleOnSpinBoxValueChanged);
	}
}

void UScalarValue_SpinBox::NativeDestruct()
{
	Super::NativeDestruct();

	if (SpinBox_PropertyValue)
	{
		SpinBox_PropertyValue->OnValueChanged.RemoveAll(this);
	}
}

void UScalarValue_SpinBox::HandleOnSpinBoxValueChanged(float InValue)
{
	if (ScalarPropertyValueViewModel)
	{
		ScalarPropertyValueViewModel->SetCurrentValue(InValue);
		ScalarPropertyValueViewModel->NotifyPropertyChanged(EPropertyChangedReason::UserInput);
	}
}

void UScalarValue_SpinBox::OnCurrentValueChanged_Implementation(double CurrentValue)
{
	Super::OnCurrentValueChanged_Implementation(CurrentValue);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		SpinBox_PropertyValue->SetValue(CurrentValue);
	}
}

void UScalarValue_SpinBox::OnNormalizedCurrentValueChanged_Implementation(double NormalizedCurrentValue)
{
	Super::OnNormalizedCurrentValueChanged_Implementation(NormalizedCurrentValue);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		SpinBox_PropertyValue->SetValue(NormalizedCurrentValue);
	}
}

void UScalarValue_SpinBox::OnValueStepChanged_Implementation(double ValueStep)
{
	Super::OnValueStepChanged_Implementation(ValueStep);

	if (SpinBox_PropertyValue)
	{
		SpinBox_PropertyValue->SetDelta(ValueStep);
	}
}

void UScalarValue_SpinBox::OnIsClampValueRangeChanged_Implementation(bool IsClampValueRange)
{
	Super::OnIsClampValueRangeChanged_Implementation(IsClampValueRange);

	if (SpinBox_PropertyValue && !IsClampValueRange)
	{
		SpinBox_PropertyValue->ClearMinValue();
		SpinBox_PropertyValue->ClearMaxValue();
	}
}

void UScalarValue_SpinBox::OnValueRangeChanged_Implementation(FVector2D ValueRange)
{
	Super::OnValueRangeChanged_Implementation(ValueRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->IsClampValueRange && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		SpinBox_PropertyValue->SetMinValue(ValueRange.X);
		SpinBox_PropertyValue->SetMaxValue(ValueRange.Y);
	}
}

void UScalarValue_SpinBox::OnNormalizedValueRangeChanged_Implementation(FVector2D NormalizedValueRange)
{
	Super::OnNormalizedValueRangeChanged_Implementation(NormalizedValueRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->IsClampValueRange && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		SpinBox_PropertyValue->SetMinValue(NormalizedValueRange.X);
		SpinBox_PropertyValue->SetMaxValue(NormalizedValueRange.Y);
	}
}

void UScalarValue_SpinBox::OnIsClampInteractionRangeChanged_Implementation(bool IsClampInteractionRange)
{
	Super::OnIsClampInteractionRangeChanged_Implementation(IsClampInteractionRange);

	if (SpinBox_PropertyValue && !IsClampInteractionRange)
	{
		SpinBox_PropertyValue->ClearMinSliderValue();
		SpinBox_PropertyValue->ClearMaxSliderValue();
	}
}

void UScalarValue_SpinBox::OnValueInteractionRangeChanged_Implementation(FVector2D ValueInteractionRange)
{
	Super::OnValueInteractionRangeChanged_Implementation(ValueInteractionRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->IsClampInteractionRange && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		SpinBox_PropertyValue->SetMinSliderValue(ValueInteractionRange.X);
		SpinBox_PropertyValue->SetMaxSliderValue(ValueInteractionRange.Y);
	}
}

void UScalarValue_SpinBox::OnNormalizedValueInteractionRangeChanged_Implementation(FVector2D NormalizedValueInteractionRange)
{
	Super::OnNormalizedValueInteractionRangeChanged_Implementation(NormalizedValueInteractionRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->IsClampInteractionRange && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		SpinBox_PropertyValue->SetMinSliderValue(NormalizedValueInteractionRange.X);
		SpinBox_PropertyValue->SetMaxSliderValue(NormalizedValueInteractionRange.Y);
	}
}

void UScalarValue_SpinBox::OnDisplayFormatChanged_Implementation(EScalarPropertyValueDisplayFormat DisplayFormat)
{
	Super::OnDisplayFormatChanged_Implementation(DisplayFormat);

	if (ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsCustom)
	{
		RefreshSpinBoxCustom();
	}
}

void UScalarValue_SpinBox::RefreshSpinBoxCustom_Implementation()
{
}
