// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/Value/ActionValue_Button.h"

#include "WidgetType.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MVVM/Action/ActionPropertyValueViewModel.h"

void UActionValue_Button::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (Button_PropertyValue)
	{
		Button_PropertyValue->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleOnButtonClicked);

		if (UActionPropertyValueViewModel* ViewModel = GetPropertyViewModel<UActionPropertyValueViewModel>())
		{
			REGISTER_MVVM_PROPERTY(ViewModel, ActionText, OnActionTextChanged, true)
		}
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

void UActionValue_Button::HandleOnButtonClicked()
{
	OnActionExecute();
	ActionPropertyValueViewModel->ExecuteAction(EPropertyChangedReason::UserInput);
	ActionPropertyValueViewModel->NotifyPropertyChanged(EPropertyChangedReason::UserInput);
}

void UActionValue_Button::OnActionTextChanged_Implementation(const FText& InActionText)
{
	if (Text_PropertyValue)
	{
		Text_PropertyValue->SetText(InActionText);
	}
}

void UActionValue_Button::OnActionExecute_Implementation()
{
}
