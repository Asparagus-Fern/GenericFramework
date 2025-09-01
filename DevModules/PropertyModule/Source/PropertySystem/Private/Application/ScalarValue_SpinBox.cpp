// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Application/ScalarValue_SpinBox.h"

#include "Components/SpinBox.h"

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

void UScalarValue_SpinBox::OnValueRangeChanged_Implementation(FVector2D ValueRange)
{
	Super::OnValueRangeChanged_Implementation(ValueRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		SpinBox_PropertyValue->SetMinValue(ValueRange.X);
		SpinBox_PropertyValue->SetMaxValue(ValueRange.Y);
	}
}

void UScalarValue_SpinBox::OnNormalizedValueRangeChanged_Implementation(FVector2D NormalizedValueRange)
{
	Super::OnNormalizedValueRangeChanged_Implementation(NormalizedValueRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		SpinBox_PropertyValue->SetMinValue(NormalizedValueRange.X);
		SpinBox_PropertyValue->SetMaxValue(NormalizedValueRange.Y);
	}
}

void UScalarValue_SpinBox::OnValueInteractionRangeChanged_Implementation(FVector2D ValueInteractionRange)
{
	Super::OnValueInteractionRangeChanged_Implementation(ValueInteractionRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		SpinBox_PropertyValue->SetMinSliderValue(ValueInteractionRange.X);
		SpinBox_PropertyValue->SetMaxSliderValue(ValueInteractionRange.Y);
	}
}

void UScalarValue_SpinBox::OnNormalizedValueInteractionRangeChanged_Implementation(FVector2D NormalizedValueInteractionRange)
{
	Super::OnNormalizedValueInteractionRangeChanged_Implementation(NormalizedValueInteractionRange);

	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		SpinBox_PropertyValue->SetMinSliderValue(NormalizedValueInteractionRange.X);
		SpinBox_PropertyValue->SetMaxSliderValue(NormalizedValueInteractionRange.Y);
	}
}

void UScalarValue_SpinBox::OnDisplayFormatChanged_Implementation(EScalarPropertyValueDisplayFormat DisplayFormat)
{
	Super::OnDisplayFormatChanged_Implementation(DisplayFormat);
	RefreshSpinBox();
}

void UScalarValue_SpinBox::RefreshSpinBox()
{
	if (SpinBox_PropertyValue && ScalarPropertyValueViewModel)
	{
		switch (ScalarPropertyValueViewModel->DisplayFormat)
		{
		case EScalarPropertyValueDisplayFormat::DisplayAsRawValue:
			SpinBox_PropertyValue->SetValue(ScalarPropertyValueViewModel->CurrentValue);
			SpinBox_PropertyValue->SetMinValue(ScalarPropertyValueViewModel->ValueRange.X);
			SpinBox_PropertyValue->SetMaxValue(ScalarPropertyValueViewModel->ValueRange.Y);
			SpinBox_PropertyValue->SetMinSliderValue(ScalarPropertyValueViewModel->ValueInteractionRange.X);
			SpinBox_PropertyValue->SetMaxSliderValue(ScalarPropertyValueViewModel->ValueInteractionRange.Y);
			break;

		case EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue:
			SpinBox_PropertyValue->SetValue(ScalarPropertyValueViewModel->NormalizedCurrentValue);
			SpinBox_PropertyValue->SetMinValue(ScalarPropertyValueViewModel->NormalizedValueRange.X);
			SpinBox_PropertyValue->SetMaxValue(ScalarPropertyValueViewModel->NormalizedValueRange.Y);
			SpinBox_PropertyValue->SetMinSliderValue(ScalarPropertyValueViewModel->NormalizedValueInteractionRange.X);
			SpinBox_PropertyValue->SetMaxSliderValue(ScalarPropertyValueViewModel->NormalizedValueInteractionRange.Y);
			break;

		case EScalarPropertyValueDisplayFormat::DisplayAsCustom:
			RefreshSpinBoxCustom();
			break;
		}
	}
}

void UScalarValue_SpinBox::RefreshSpinBoxCustom_Implementation()
{
}
