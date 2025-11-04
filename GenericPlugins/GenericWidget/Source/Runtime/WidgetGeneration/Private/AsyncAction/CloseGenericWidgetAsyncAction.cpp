// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/CloseGenericWidgetAsyncAction.h"

#include "GenericGameSlotSubsystem.h"
#include "GenericWidgetSubsystem.h"


void UCloseGenericWidgetAsyncAction::Activate()
{
	Super::Activate();

	if (!Widget)
	{
		FFrame::KismetExecutionMessage(TEXT("Close Generic Widget Must Provide a Widget."), ELogVerbosity::Error);
		return;
	}

	Widget->GetOnWidgetInactiveAnimationPlayFinish().AddUObject(this, &UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
	if (UGenericWidgetSubsystem* GenericWidgetManager = UGenericWidgetSubsystem::Get(WorldContextObject))
	{
		GenericWidgetManager->CloseGenericWidget(Widget, bMarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(this, &UCloseGenericWidgetAsyncAction::OnWidgetInactived));
	}
}

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidgetByTag(UObject* InWorldContextObject, const FGameplayTag InSlotTag, const bool MarkAsGarbage)
{
	check(InSlotTag.IsValid())

	if (UGenericGameSlotSubsystem* GameSlotSubsystem = UGenericGameSlotSubsystem::Get(InWorldContextObject))
	{
		if (UGenericWidget* GameSlotWidget = GameSlotSubsystem->GetSlotWidget(InSlotTag))
		{
			return AsyncCloseGenericWidget(InWorldContextObject, GameSlotWidget, MarkAsGarbage);
		}
	}

	return nullptr;
}

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidget(UObject* InWorldContextObject, UGenericWidget* InWidget, const bool MarkAsGarbage)
{
	check(InWidget)

	UCloseGenericWidgetAsyncAction* NewAction = NewObject<UCloseGenericWidgetAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->Widget = InWidget;
	NewAction->bMarkAsGarbage = MarkAsGarbage;

	return NewAction;
}

void UCloseGenericWidgetAsyncAction::OnWidgetInactived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast();
}

void UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetInactiveAnimationPlayFinish().RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
