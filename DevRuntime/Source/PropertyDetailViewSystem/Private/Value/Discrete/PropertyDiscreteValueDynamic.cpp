// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic.h"

void UPropertyDiscreteValueDynamic::Startup()
{
	Getter->Startup(Context, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyDiscreteValueDynamic::OnDataSourcesReady()
{
	StartupComplete();
}

void UPropertyDiscreteValueDynamic::StoreInitial()
{
	InitialValue = GetValueAsString();
}

void UPropertyDiscreteValueDynamic::ResetToDefault()
{
	if (DefaultValue.IsSet())
	{
		SetValueFromString(DefaultValue.GetValue(), EPropertyChangeReason::ResetToDefault);
	}
}

void UPropertyDiscreteValueDynamic::RestoreToInitial()
{
	SetValueFromString(InitialValue, EPropertyChangeReason::RestoreToInitial);
}

void UPropertyDiscreteValueDynamic::SetDiscreteOptionByIndex(int32 Index)
{
	if (ensure(OptionValues.IsValidIndex(Index)))
	{
		SetValueFromString(OptionValues[Index]);
	}
}

int32 UPropertyDiscreteValueDynamic::GetDiscreteOptionIndex() const
{
	const FString CurrentValue = GetValueAsString();
	const int32 Index = OptionValues.IndexOfByPredicate([this, CurrentValue](const FString& InOption)
		{
			return CurrentValue == InOption;
		}
	);

	if (Index == INDEX_NONE)
	{
		return GetDiscreteOptionDefaultIndex();
	}

	return Index;
}

int32 UPropertyDiscreteValueDynamic::GetDiscreteOptionDefaultIndex() const
{
	if (DefaultValue.IsSet())
	{
		return OptionValues.IndexOfByPredicate([this](const FString& InOption)
			{
				return DefaultValue.GetValue() == InOption;
			}
		);
	}

	return INDEX_NONE;
}

TArray<FText> UPropertyDiscreteValueDynamic::GetDiscreteOptions() const
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

void UPropertyDiscreteValueDynamic::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void UPropertyDiscreteValueDynamic::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

void UPropertyDiscreteValueDynamic::SetDefaultValueFromString(FString InOptionValue)
{
	DefaultValue = InOptionValue;
}

void UPropertyDiscreteValueDynamic::AddOption(FString InOptionValue, FText InOptionText)
{
#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(!OptionValues.Contains(InOptionValue), TEXT("You Already Added This Option, InOptionValue: %s InOptionText %s."), *InOptionValue, *InOptionText.ToString());
#endif

	OptionValues.Add(InOptionValue);
	OptionDisplayTexts.Add(InOptionText);
}

void UPropertyDiscreteValueDynamic::RemoveOption(FString InOptionValue)
{
	const int32 Index = OptionValues.IndexOfByKey(InOptionValue);
	if (Index != INDEX_NONE)
	{
		OptionValues.RemoveAt(Index);
		OptionDisplayTexts.RemoveAt(Index);
	}
}

const TArray<FString>& UPropertyDiscreteValueDynamic::GetOptionValues()
{
	return OptionValues;
}

bool UPropertyDiscreteValueDynamic::HasOption(const FString& InOptionValue)
{
	return OptionValues.Contains(InOptionValue);
}

FString UPropertyDiscreteValueDynamic::GetValueAsString() const
{
	return Getter->GetValueAsString(Context);
}

void UPropertyDiscreteValueDynamic::SetValueFromString(FString InStringValue)
{
	SetValueFromString(InStringValue, EPropertyChangeReason::Change);
}

void UPropertyDiscreteValueDynamic::SetValueFromString(FString InStringValue, EPropertyChangeReason Reason)
{
	Setter->SetValue(Context, InStringValue);
	NotifyPropertyChanged(Reason);
}
