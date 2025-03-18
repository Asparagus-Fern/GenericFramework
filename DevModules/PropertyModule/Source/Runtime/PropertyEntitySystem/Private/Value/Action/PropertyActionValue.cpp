// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Action/PropertyActionValue.h"

FText UPropertyActionValue::GetActionText() const
{
	return ActionText;
}

void UPropertyActionValue::SetActionText(FText InActionText)
{
	ActionText = InActionText;
}

void UPropertyActionValue::ExecuteAction()
{
	Action.ExecuteIfBound(this);
	DynamicAction.ExecuteIfBound(this);
	NotifyPropertyChanged(EPropertyChangeReason::Change);
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

void UPropertyActionValue::SetDynamicAction(FOnExecutePropertyDynamicAction InDynamicAction)
{
	DynamicAction = InDynamicAction;
}
