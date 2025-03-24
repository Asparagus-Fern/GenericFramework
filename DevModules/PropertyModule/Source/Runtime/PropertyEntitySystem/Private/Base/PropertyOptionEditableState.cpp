// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Base/PropertyOptionEditableState.h"

UPropertyOptionEditableState::UPropertyOptionEditableState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPropertyOptionEditableState::SetOptionEnabled(const FString& InOption, bool InEnabled)
{
	if (InEnabled && !DisabledOptions.Contains(InOption))
	{
		DisabledOptions.Add(InOption);
	}
	else if (!InEnabled && DisabledOptions.Contains(InOption))
	{
		DisabledOptions.Remove(InOption);
	}
}

void UPropertyOptionEditableState::SetOptionVisible(FString InOption, bool InVisible)
{
	if (InVisible && !HiddenOptions.Contains(InOption))
	{
		HiddenOptions.Add(InOption);
	}
	else if (!InVisible && HiddenOptions.Contains(InOption))
	{
		HiddenOptions.Remove(InOption);
	}
}
