// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Action/PropertyActionValue.h"

FText UPropertyActionValue::GetActionText() const
{
	return ActionText;
}

void UPropertyActionValue::SetActionText(FText InActionText)
{
	ActionText = InActionText;
}

void UPropertyActionValue::SetAction(const FOnExecutePropertyAction& InAction)
{
	Action = InAction;
}

void UPropertyActionValue::SetAction(TFunction<void(UPropertyEntity*)> InAction)
{
	Action = FOnExecutePropertyAction::CreateLambda([InAction](UPropertyEntity* InPropertyEntity)
		{
			InAction(InPropertyEntity);
		}
	);
}

void UPropertyActionValue::SetDynamicAction(FOnExecuteDynamicPropertyAction InAction)
{
	Action = FOnExecutePropertyAction::CreateLambda([InAction](UPropertyEntity* InPropertyEntity)
		{
			InAction.ExecuteIfBound(InPropertyEntity);
		}
	);
}

void UPropertyActionValue::ExecuteAction()
{
	Action.ExecuteIfBound(this);
	NotifyPropertyChanged(EPropertyChangeReason::Change);
}
