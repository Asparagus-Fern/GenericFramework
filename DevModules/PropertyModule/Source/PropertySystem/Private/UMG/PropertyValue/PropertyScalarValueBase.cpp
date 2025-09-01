// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyScalarValueBase.h"

#include "WidgetType.h"
#include "MVVM/Scalar/ScalarPropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertyScalarValueBase::GetSupportPropertyViewModelClass()
{
	return UScalarPropertyValueViewModel::StaticClass();
}

void UPropertyScalarValueBase::PostInitPropertyViewModel()
{
	Super::PostInitPropertyViewModel();

	if (UScalarPropertyValueViewModel* ViewModel = GetPropertyViewModel<UScalarPropertyValueViewModel>())
	{
		ScalarPropertyValueViewModel = ViewModel;
	}
}

void UPropertyScalarValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (ScalarPropertyValueViewModel)
	{
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, DefaultValue, OnDefaultValueChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedDefaultValue, OnNormalizedDefaultValueChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, CurrentValue, OnCurrentValueChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedCurrentValue, OnNormalizedCurrentValueChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueStep, OnValueStepChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueRange, OnValueRangeChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedValueRange, OnNormalizedValueRangeChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueInteractionRange, OnValueInteractionRangeChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedValueInteractionRange, OnNormalizedValueInteractionRangeChanged, false)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, DisplayFormat, OnDisplayFormatChanged, true)
	}
}

void UPropertyScalarValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();
}

void UPropertyScalarValueBase::OnDefaultValueChanged_Implementation(double DefaultValue)
{
}

void UPropertyScalarValueBase::OnNormalizedDefaultValueChanged_Implementation(double NormalizedDefaultValue)
{
}

void UPropertyScalarValueBase::OnCurrentValueChanged_Implementation(double CurrentValue)
{
}

void UPropertyScalarValueBase::OnNormalizedCurrentValueChanged_Implementation(double NormalizedCurrentValue)
{
}

void UPropertyScalarValueBase::OnValueStepChanged_Implementation(double ValueStep)
{
}

void UPropertyScalarValueBase::OnValueRangeChanged_Implementation(FVector2D ValueRange)
{
}

void UPropertyScalarValueBase::OnNormalizedValueRangeChanged_Implementation(FVector2D NormalizedValueRange)
{
}

void UPropertyScalarValueBase::OnValueInteractionRangeChanged_Implementation(FVector2D ValueInteractionRange)
{
}

void UPropertyScalarValueBase::OnNormalizedValueInteractionRangeChanged_Implementation(FVector2D NormalizedValueInteractionRange)
{
}

void UPropertyScalarValueBase::OnDisplayFormatChanged_Implementation(EScalarPropertyValueDisplayFormat DisplayFormat)
{
}
