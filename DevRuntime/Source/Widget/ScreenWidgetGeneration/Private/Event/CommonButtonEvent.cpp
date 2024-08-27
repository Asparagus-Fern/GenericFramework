// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CommonButtonEvent.h"

#include "Event/CommonButtonCondition.h"

void UCommonButtonEvent::NativeOnActived()
{
	Super::NativeOnActived();

	bool IsConditionPass = true;
	// for (const auto& Condition : CommonButtonConditions)
	// {
	// 	if (!Condition->IsConditionPass())
	// 	{
	// 		IsConditionPass = false;
	// 		break;
	// 	}
	// }

	if (IsConditionPass)
	{
		ExecuteButtonEvent();
	}
}

void UCommonButtonEvent::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (bIsAsync)
	{
		MarkAsInactivedFinish();
	}
}

bool UCommonButtonEvent::CanExecuteButtonEvent_Implementation()
{
	return true;
}

void UCommonButtonEvent::ExecuteButtonEvent_Implementation()
{
}
