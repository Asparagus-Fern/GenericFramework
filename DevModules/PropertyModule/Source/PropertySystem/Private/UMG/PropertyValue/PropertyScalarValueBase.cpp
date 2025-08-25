// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyScalarValueBase.h"

#include "PropertyType.h"
#include "MVVM/Scalar/ScalarPropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertyScalarValueBase::GetSupportViewModelClass()
{
	return UScalarPropertyValueViewModel::StaticClass();
}

void UPropertyScalarValueBase::PostInitViewModelProperty()
{
	Super::PostInitViewModelProperty();

	if (UScalarPropertyValueViewModel* ViewModel = GetViewModel<UScalarPropertyValueViewModel>())
	{
		ScalarPropertyValueViewModel = ViewModel;
	}
}

void UPropertyScalarValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (ScalarPropertyValueViewModel)
	{
		MVVM_REGISTRY_ONLY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, DefaultValue, HandleOnDefaultValueChanged)
		MVVM_REGISTRY_ONLY(OnNormalizedDefaultValueChangedHandle, ScalarPropertyValueViewModel, NormalizedDefaultValue, HandleOnNormalizedDefaultValueChanged)
		MVVM_REGISTRY_ONLY(OnCurrentValueChangedHandle, ScalarPropertyValueViewModel, CurrentValue, HandleOnCurrentValueChanged)
		MVVM_REGISTRY_ONLY(OnNormalizedCurrentValueChangedHandle, ScalarPropertyValueViewModel, NormalizedCurrentValue, HandleOnNormalizedCurrentValueChanged)
		MVVM_REGISTRY_ONLY(OnValueStepChangedHandle, ScalarPropertyValueViewModel, ValueStep, HandleOnValueStepChanged)
		MVVM_REGISTRY_ONLY(OnValueRangeChangedHandle, ScalarPropertyValueViewModel, ValueRange, HandleOnValueRangeChanged)
		MVVM_REGISTRY_ONLY(OnNormalizedValueRangeChangedHandle, ScalarPropertyValueViewModel, NormalizedValueRange, HandleOnNormalizedValueRangeChanged)
		MVVM_REGISTRY_ONLY(OnValueInteractionRangeChangedHandle, ScalarPropertyValueViewModel, ValueInteractionRange, HandleOnValueInteractionRangeChanged)
		MVVM_REGISTRY_ONLY(OnNormalizedValueInteractionRangeChangedHandle, ScalarPropertyValueViewModel, NormalizedValueInteractionRange, HandleOnNormalizedValueInteractionRangeChanged)
		MVVM_REGISTRY(OnDisplayFormatChangedHandle, ScalarPropertyValueViewModel, DisplayFormat, HandleOnDisplayFormatChanged)
	}
}

void UPropertyScalarValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (ScalarPropertyValueViewModel)
	{
		MVVM_UNREGISTRY(OnDisplayFormatChangedHandle, ScalarPropertyValueViewModel, DisplayFormat)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, DefaultValue)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, NormalizedDefaultValue)
		MVVM_UNREGISTRY(OnCurrentValueChangedHandle, ScalarPropertyValueViewModel, CurrentValue)
		MVVM_UNREGISTRY(OnCurrentValueChangedHandle, ScalarPropertyValueViewModel, NormalizedCurrentValue)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, ValueStep)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, ValueRange)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, NormalizedValueRange)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, ValueInteractionRange)
		MVVM_UNREGISTRY(OnDefaultValueChangedHandle, ScalarPropertyValueViewModel, NormalizedValueInteractionRange)
	}
}

void UPropertyScalarValueBase::HandleOnDisplayFormatChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	if (ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsRawValue)
	{
		HandleOnDefaultValueChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::DefaultValue);
		HandleOnCurrentValueChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::CurrentValue);
		HandleOnValueRangeChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::ValueRange);
		HandleOnValueInteractionRangeChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::ValueInteractionRange);
	}
	else if (ScalarPropertyValueViewModel->DisplayFormat == EScalarPropertyValueDisplayFormat::DisplayAsNormalizedValue)
	{
		HandleOnNormalizedDefaultValueChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::NormalizedDefaultValue);
		HandleOnNormalizedCurrentValueChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::NormalizedCurrentValue);
		HandleOnNormalizedValueRangeChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::NormalizedValueRange);
		HandleOnNormalizedValueInteractionRangeChanged(this, UScalarPropertyValueViewModel::FFieldNotificationClassDescriptor::NormalizedValueInteractionRange);
	}
	else
	{
		UpdateCustomDisplayFormat();
	}
}

void UPropertyScalarValueBase::HandleOnDefaultValueChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnDefaultValueChanged(ScalarPropertyValueViewModel->DefaultValue);
}

void UPropertyScalarValueBase::HandleOnNormalizedDefaultValueChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnNormalizedDefaultValueChanged(ScalarPropertyValueViewModel->GetNormalizedDefaultValue());
}

void UPropertyScalarValueBase::HandleOnCurrentValueChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnCurrentValueChanged(ScalarPropertyValueViewModel->CurrentValue);
}

void UPropertyScalarValueBase::HandleOnNormalizedCurrentValueChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnNormalizedCurrentValueChanged(ScalarPropertyValueViewModel->GetNormalizedCurrentValue());
}

void UPropertyScalarValueBase::HandleOnValueStepChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnValueStepChanged(ScalarPropertyValueViewModel->ValueStep);
}

void UPropertyScalarValueBase::HandleOnValueRangeChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnValueRangeChanged(ScalarPropertyValueViewModel->ValueRange);
}

void UPropertyScalarValueBase::HandleOnNormalizedValueRangeChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnNormalizedValueRangeChanged(ScalarPropertyValueViewModel->GetNormalizedValueRange());
}

void UPropertyScalarValueBase::HandleOnValueInteractionRangeChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnValueInteractionRangeChanged(ScalarPropertyValueViewModel->ValueInteractionRange);
}

void UPropertyScalarValueBase::HandleOnNormalizedValueInteractionRangeChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnNormalizedValueInteractionRangeChanged(ScalarPropertyValueViewModel->GetNormalizedValueInteractionRange());
}

void UPropertyScalarValueBase::UpdateCustomDisplayFormat_Implementation()
{
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
