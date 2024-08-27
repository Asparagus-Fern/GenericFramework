// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_CloseUserWidget.h"

#include "ScreenWidgetManager.h"

bool UCBE_CloseUserWidget::CanExecuteButtonEvent_Implementation()
{
	return !GetValidSlotTags().IsEmpty();
}

void UCBE_CloseUserWidget::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (bIsAsync)
	{
		TArray<FGameplayTag> ValidSlotTags = GetValidSlotTags();
		if (ValidSlotTags.IsValidIndex(CloseWidgetIndex))
		{
			const auto OnCloseFinish = FOnWidgetActiveStateChanged::CreateLambda([this](UUserWidgetBase*)
				{
					CloseWidgetIndex++;
					ExecuteButtonEvent();
				}
			);

			GetManager<UScreenWidgetManager>()->CloseUserWidget(ValidSlotTags[CloseWidgetIndex], OnCloseFinish);
		}
		else
		{
			CloseWidgetIndex = 0;
			MarkAsActivedFinish();
		}
	}
	else
	{
		TArray<FGameplayTag> ValidSlotTags = GetValidSlotTags();
		for (const auto& ValidWidget : ValidSlotTags)
		{
			GetManager<UScreenWidgetManager>()->CloseUserWidget(ValidWidget);
		}
	}
}

TArray<FGameplayTag> UCBE_CloseUserWidget::GetValidSlotTags()
{
	TArray<FGameplayTag> ValidSlotTags;

	for (auto& SlotTag : SlotTags)
	{
		if (SlotTag.IsValid())
		{
			ValidSlotTags.AddUnique(SlotTag);
		}
	}

	return ValidSlotTags;
}
