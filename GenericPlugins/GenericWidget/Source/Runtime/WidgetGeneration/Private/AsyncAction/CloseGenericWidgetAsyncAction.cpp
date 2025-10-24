// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/CloseGenericWidgetAsyncAction.h"

#include "GenericGameSlotManager.h"
#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

void UCloseGenericWidgetAsyncAction::Activate()
{
	Super::Activate();

	if (!Widget)
	{
		FFrame::KismetExecutionMessage(TEXT("Close Generic Widget Must Provide a Widget."), ELogVerbosity::Error);
		return;
	}

	Widget->GetOnWidgetInactiveAnimationPlayFinish().AddUObject(this, &UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
	FWidgetHelper::CloseGenericWidget(Widget, bMarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(this, &UCloseGenericWidgetAsyncAction::OnWidgetInactived));
}

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidget(UGenericWidget* InWidget, const bool MarkAsGarbage)
{
	check(InWidget)

	UCloseGenericWidgetAsyncAction* NewAction = NewObject<UCloseGenericWidgetAsyncAction>();
	NewAction->Widget = InWidget;
	NewAction->bMarkAsGarbage = MarkAsGarbage;

	return NewAction;
}

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidgetByTag(const FGameplayTag InSlotTag, const bool MarkAsGarbage)
{
	check(InSlotTag.IsValid())

	if (UGenericGameSlotManager* GameSlotManager = GetManagerOwner<UGenericGameSlotManager>())
	{
		if (UGenericWidget* GameSlotWidget = GameSlotManager->GetSlotWidget(InSlotTag))
		{
			return AsyncCloseGenericWidget(GameSlotWidget, MarkAsGarbage);
		}
	}

	return nullptr;
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
