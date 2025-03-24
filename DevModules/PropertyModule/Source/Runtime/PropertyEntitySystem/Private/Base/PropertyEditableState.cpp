// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Base/PropertyEditableState.h"

UPropertyEditableState::UPropertyEditableState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bEnabled(true),
	  bVisible(true),
	  bResetable(true)
{
	OptionEditState = CreateDefaultSubobject<UPropertyOptionEditableState>("OptionEditState");
}

void UPropertyEditableState::SetEnabled(bool InEnabled)
{
	bEnabled = InEnabled;
}

void UPropertyEditableState::SetVisible(bool InVisible)
{
	bVisible = InVisible;
}

void UPropertyEditableState::SetResetable(bool InResetable)
{
	bResetable = InResetable;
}

void UPropertyEditableState::SetOptionEnabled(const FString& InOption, bool InEnabled)
{
	OptionEditState->SetOptionEnabled(InOption, InEnabled);
}

void UPropertyEditableState::SetOptionVisible(FString InOption, bool InVisible)
{
	OptionEditState->SetOptionVisible(InOption, InVisible);
}

TArray<FString> UPropertyEditableState::GetDisabledOptions() const
{
	return OptionEditState->GetDisabledOptions();
}

TArray<FString> UPropertyEditableState::GetHiddenOptions() const
{
	return OptionEditState->GetHiddenOptions();
}
