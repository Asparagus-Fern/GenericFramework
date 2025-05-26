// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue.h"

#include "Base/PropertyDataSource.h"

void UPropertyDiscreteValue::OnInitialized()
{
	/* 确保Getter和Setter的属性路径能从Context获取 */
#if !UE_BUILD_SHIPPING
	ensureAlways(Getter);
	ensureAlwaysMsgf(Getter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
	ensureAlways(Setter);
	ensureAlwaysMsgf(Setter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
#endif

	Super::OnInitialized();
}

void UPropertyDiscreteValue::Startup()
{
	Getter->Startup(Context, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyDiscreteValue::OnDataSourcesReady()
{
	StartupComplete();
}

void UPropertyDiscreteValue::StoreInitial()
{
	InitialValue = GetValueAsString();
}

void UPropertyDiscreteValue::ResetToInitial()
{
	SetValueFromString(InitialValue, EPropertyChangeReason::RestoreToInitial);
}

void UPropertyDiscreteValue::ResetToDefault()
{
	if (DefaultValue.IsSet())
	{
		SetValueFromString(DefaultValue.GetValue(), EPropertyChangeReason::ResetToDefault);
	}
}

FString UPropertyDiscreteValue::GetValueAsString() const
{
	return Getter->GetValueAsString(Context);
}

void UPropertyDiscreteValue::SetValueFromString(FString InStringValue)
{
	SetValueFromString(InStringValue, EPropertyChangeReason::Change);
}

void UPropertyDiscreteValue::SetValueFromString(FString InStringValue, EPropertyChangeReason Reason)
{
	Setter->SetValueByString(Context, InStringValue);
	NotifyPropertyChanged(Reason);
}

const TArray<FString>& UPropertyDiscreteValue::GetAllOptionValue()
{
	return FPropertyDiscreteValueInterface::GetAllOptionValue();
}

TArray<FText> UPropertyDiscreteValue::GetAllOptionText() const
{
	const TArray<FString>& DisabledOptions = GetPropertyEditableState().GetDisabledOptions();

	if (DisabledOptions.Num() > 0)
	{
		TArray<FText> AllowedOptions;

		for (int32 OptionIndex = 0; OptionIndex < OptionValues.Num(); ++OptionIndex)
		{
			if (!DisabledOptions.Contains(OptionValues[OptionIndex]))
			{
				AllowedOptions.Add(OptionDisplayTexts[OptionIndex]);
			}
		}

		return AllowedOptions;
	}

	return OptionDisplayTexts;
}











