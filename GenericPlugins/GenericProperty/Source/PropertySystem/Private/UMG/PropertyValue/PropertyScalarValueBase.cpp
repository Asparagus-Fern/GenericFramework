// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyScalarValueBase.h"

#include "WidgetType.h"
#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"

TSubclassOf<UPropertyViewModel> UPropertyScalarValueBase::GetSupportPropertyViewModelClass()
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
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, DisplayFormat, OnDisplayFormatChanged, true)

		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, InitialValue, OnInitialValueChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedInitialValue, OnNormalizedInitialValueChanged, true)

		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, CurrentValue, OnCurrentValueChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedCurrentValue, OnNormalizedCurrentValueChanged, true)

		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueStep, OnValueStepChanged, true)

		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, IsClampValueRange, OnIsClampValueRangeChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueRange, OnValueRangeChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedValueRange, OnNormalizedValueRangeChanged, true)

		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, IsClampInteractionRange, OnIsClampInteractionRangeChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, ValueInteractionRange, OnValueInteractionRangeChanged, true)
		REGISTER_MVVM_PROPERTY(ScalarPropertyValueViewModel, NormalizedValueInteractionRange, OnNormalizedValueInteractionRangeChanged, true)
	}
}

void UPropertyScalarValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();
}

void UPropertyScalarValueBase::OnInitialValueChanged_Implementation(double DefaultValue)
{
}

void UPropertyScalarValueBase::OnNormalizedInitialValueChanged_Implementation(double NormalizedDefaultValue)
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

void UPropertyScalarValueBase::OnIsClampValueRangeChanged_Implementation(bool IsClampValueRange)
{
}

void UPropertyScalarValueBase::OnNormalizedValueRangeChanged_Implementation(FVector2D NormalizedValueRange)
{
}

void UPropertyScalarValueBase::OnIsClampInteractionRangeChanged_Implementation(bool IsIsClampInteractionRange)
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
