// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Value/Discrete/PropertyDiscreteValueInterface.h"

void FPropertyDiscreteValueInterface::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void FPropertyDiscreteValueInterface::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

FString FPropertyDiscreteValueInterface::GetDefaultValueAsString() const
{
	if (DefaultValue.IsSet())
	{
		return DefaultValue.GetValue();
	}

	return TEXT("");
}

void FPropertyDiscreteValueInterface::SetDefaultValueFromString(const FString& InOptionValue)
{
	DefaultValue = InOptionValue;
}

bool FPropertyDiscreteValueInterface::HasOption(const FString& InOptionValue)
{
	return OptionValues.Contains(InOptionValue);
}

const TArray<FString>& FPropertyDiscreteValueInterface::GetAllOptionValue()
{
	return OptionValues;
}

TArray<FText> FPropertyDiscreteValueInterface::GetAllOptionText() const
{
	return OptionDisplayTexts;
}

void FPropertyDiscreteValueInterface::AddOption(const FString& InOptionValue, const FText& InOptionText)
{
#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(!OptionValues.Contains(InOptionValue), TEXT("You Already Added This Option, InOptionValue: %s InOptionText %s."), *InOptionValue, *InOptionText.ToString());
#endif

	OptionValues.Add(InOptionValue);
	OptionDisplayTexts.Add(InOptionText);
}

void FPropertyDiscreteValueInterface::RemoveOption(const FString& InOptionValue)
{
	const int32 Index = OptionValues.IndexOfByKey(InOptionValue);
	if (Index != INDEX_NONE)
	{
		OptionValues.RemoveAt(Index);
		OptionDisplayTexts.RemoveAt(Index);
	}
}

int32 FPropertyDiscreteValueInterface::GetDiscreteOptionIndex() const
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

void FPropertyDiscreteValueInterface::SetDiscreteOptionByIndex(int32 Index)
{
	if (ensure(OptionValues.IsValidIndex(Index)))
	{
		SetValueFromString(OptionValues[Index]);
	}
}

int32 FPropertyDiscreteValueInterface::GetDiscreteOptionDefaultIndex() const
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

void FPropertyDiscreteValueInterface::SetDiscreteDefaultOptionByIndex(int32 Index)
{
	if (ensure(OptionValues.IsValidIndex(Index)))
	{
		SetDefaultValueFromString(OptionValues[Index]);
	}
}
