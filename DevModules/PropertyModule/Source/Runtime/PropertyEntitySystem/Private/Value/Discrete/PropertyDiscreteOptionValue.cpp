// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteOptionValue.h"

FString UPropertyDiscreteOption::GetOptionValue() const
{
	return OptionValue;
}

void UPropertyDiscreteOption::SetOptionValue(FString InOptionValue)
{
	OptionValue = InOptionValue;
}

void UPropertyDiscreteOptionValue::OnInitialized()
{
	Super::OnInitialized();

	for (const auto& Option : Options)
	{
		Option->Initialize(Source, Option->GetPropertyName());
	}
}

void UPropertyDiscreteOptionValue::GetChildProperties_Implementation(TArray<UPropertyEntity*>& Children)
{
	Super::GetChildProperties_Implementation(Children);

	for (auto& Option : Options)
	{
		Children.Add(Option);
	}
}

bool UPropertyDiscreteOptionValue::HasOption(FName InOptionName)
{
	for (const auto& Option : Options)
	{
		if (Option->GetPropertyName() == InOptionName)
		{
			return true;
		}
	}
	return false;
}

bool UPropertyDiscreteOptionValue::HasOption(int32 InOptionIndex)
{
	return Options.IsValidIndex(InOptionIndex);
}

bool UPropertyDiscreteOptionValue::HasOption(UPropertyDiscreteOption* InOption)
{
	for (auto& Option : Options)
	{
		if (Option == InOption)
		{
			return true;
		}
	}
	return false;
}

UPropertyDiscreteOption* UPropertyDiscreteOptionValue::GetOption(FName InOptionName)
{
	for (auto& Option : Options)
	{
		if (Option->GetPropertyName() == InOptionName)
		{
			return Option;
		}
	}
	return nullptr;
}

UPropertyDiscreteOption* UPropertyDiscreteOptionValue::GetOption(int32 InOptionIndex)
{
	if (Options.IsValidIndex(InOptionIndex))
	{
		return Options[InOptionIndex];
	}
	return nullptr;
}

UPropertyDiscreteOption* UPropertyDiscreteOptionValue::AddOption(FName InOptionName, FString InOptionValue, FText InOptionText, FText InOptionDescriptionText)
{
	UPropertyDiscreteOption* NewOption = NewObject<UPropertyDiscreteOption>(this);
	NewOption->SetOptionValue(InOptionValue);
	NewOption->SetDisplayName(InOptionText);
	NewOption->SetDescriptionText(InOptionDescriptionText);

	NewOption->Initialize(Source, InOptionName);
	
	if (!HasOption(NewOption))
	{
		Options.Add(NewOption);
	}

	return NewOption;
}

void UPropertyDiscreteOptionValue::RemoveOption(FName InOptionName)
{
	if (UPropertyDiscreteOption* Option = GetOption(InOptionName))
	{
		RemoveOption(Option);
	}
}

void UPropertyDiscreteOptionValue::RemoveOption(int32 InOptionIndex)
{
	if (UPropertyDiscreteOption* Option = GetOption(InOptionIndex))
	{
		RemoveOption(Option);
	}
}

void UPropertyDiscreteOptionValue::RemoveOption(UPropertyDiscreteOption* InOption)
{
	if (!HasOption(InOption))
	{
		DLOG(DLogProperty, Warning, TEXT("InOption Already Removed"))
		return;
	}

	Options.Remove(InOption);
}

TArray<UPropertyDiscreteOption*> UPropertyDiscreteOptionValue::GetOptions()
{
	return Options;
}
