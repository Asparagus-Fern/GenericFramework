// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_OpenUserWidget.h"

#include "ScreenWidgetManager.h"

bool UCBE_OpenUserWidget::CanExecuteButtonEvent_Implementation()
{
	return !GetValidWidgets().IsEmpty();
}

void UCBE_OpenUserWidget::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (bIsAsync)
	{
		TArray<UUserWidgetBase*> ValidWidgets = GetValidWidgets();
		if (ValidWidgets.IsValidIndex(OpenWidgetIndex))
		{
			const auto OnOpenFinish = FOnWidgetActiveStateChanged::CreateLambda([this](UUserWidgetBase*)
				{
					OpenWidgetIndex++;
					ExecuteButtonEvent();
				}
			);

			GetManager<UScreenWidgetManager>()->OpenUserWidget(ValidWidgets[OpenWidgetIndex], OnOpenFinish);
		}
		else
		{
			OpenWidgetIndex = 0;
			MarkAsActivedFinish();
		}
	}
	else
	{
		TArray<UUserWidgetBase*> ValidWidgets = GetValidWidgets();
		for (const auto& ValidWidget : ValidWidgets)
		{
			GetManager<UScreenWidgetManager>()->OpenUserWidget(ValidWidget);
		}
	}
}

TArray<UUserWidgetBase*> UCBE_OpenUserWidget::GetValidWidgets()
{
	TArray<UUserWidgetBase*> ValidWidgets;

	for (auto& OpenWidget : OpenWidgets)
	{
		UUserWidgetBase* ContainerWidget = UScreenWidgetManager::GetContainerWidget(OpenWidget);
		if (IsValid(ContainerWidget))
		{
			ValidWidgets.Add(ContainerWidget);
		}
	}

	return ValidWidgets;
}
