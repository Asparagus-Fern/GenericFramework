// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/Action/ActionPropertyValueViewModel.h"

void UActionPropertyValueViewModel::ExecuteAction(EPropertyChangedReason ChangedReason)
{
	OnActionExecuteEvent.ExecuteIfBound(this);
	NotifyPropertyChanged(ChangedReason);
}

void UActionPropertyValueViewModel::SetAction(const FOnActionPropertyExecute& InEvent)
{
	OnActionExecuteEvent = InEvent;
}

void UActionPropertyValueViewModel::SetAction(TFunction<void(UActionPropertyValueViewModel*)> InEvent)
{
	OnActionExecuteEvent = FOnActionPropertyExecute::CreateLambda([InEvent](UActionPropertyValueViewModel* InViewModel)
		{
			InEvent(InViewModel);
		}
	);
}

const FText& UActionPropertyValueViewModel::GetActionText() const
{
	return ActionText;
}

void UActionPropertyValueViewModel::SetActionText(const FText& InActionText)
{
	if (!ActionText.EqualTo(InActionText))
	{
		ActionText = InActionText;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(ActionText);
	}
}
