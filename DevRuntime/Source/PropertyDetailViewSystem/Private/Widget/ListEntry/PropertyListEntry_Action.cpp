// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ListEntry/PropertyListEntry_Action.h"

#include "CommonButtonBase.h"
#include "Value/Action/PropertyActionValue.h"

void UPropertyListEntry_Action::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);

	ActionProperty = Cast<UPropertyActionValue>(InProperty);
	check(ActionProperty)
	OnPropertyAssigned(ActionProperty->GetActionText());
}

void UPropertyListEntry_Action::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button_Action->OnClicked().AddUObject(this, &UPropertyListEntry_Action::HandleActionButtonClicked);
}

void UPropertyListEntry_Action::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();
	Button_Action = nullptr;
}

void UPropertyListEntry_Action::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	if (Button_Action)
	{
		const bool bLocalIsEnabled = InEditableState.IsEnabled();
		Button_Action->SetIsEnabled(bLocalIsEnabled);
	}
}

void UPropertyListEntry_Action::HandleActionButtonClicked()
{
	ActionProperty->ExecuteAction();
}
