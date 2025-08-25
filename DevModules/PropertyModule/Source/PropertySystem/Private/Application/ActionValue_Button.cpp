// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/ActionValue_Button.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MVVM/Action/ActionPropertyValueViewModel.h"

void UActionValue_Button::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (Button_PropertyValue)
	{
		Button_PropertyValue->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleOnButtonClicked);
	}
}

void UActionValue_Button::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (Button_PropertyValue)
	{
		Button_PropertyValue->OnClicked.RemoveAll(this);
	}
}

void UActionValue_Button::OnPropertyValueDisplayNameChanged_Implementation(const FText& InDisplayName)
{
	Super::OnPropertyValueDisplayNameChanged_Implementation(InDisplayName);

	if (Text_PropertyValue)
	{
		Text_PropertyValue->SetText(ActionPropertyValueViewModel->PropertyValueDisplayName);
	}
}

void UActionValue_Button::OnPropertyValueTooltipChanged_Implementation(const FText& InTooltip)
{
	Super::OnPropertyValueTooltipChanged_Implementation(InTooltip);

	if (Button_PropertyValue)
	{
		Button_PropertyValue->SetToolTipText(ActionPropertyValueViewModel->PropertyValueTooltip);
	}
}

void UActionValue_Button::HandleOnButtonClicked()
{
	OnActionExecute();
	ActionPropertyValueViewModel->OnPropertyActionValueExecute.Broadcast();
}

void UActionValue_Button::OnActionExecute_Implementation()
{
}
