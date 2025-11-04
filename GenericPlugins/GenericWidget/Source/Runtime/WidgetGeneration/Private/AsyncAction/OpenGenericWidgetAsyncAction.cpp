// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/OpenGenericWidgetAsyncAction.h"

#include "GenericWidgetSubsystem.h"

void UOpenGenericWidgetAsyncAction::Activate()
{
	Super::Activate();

	if (!Widget)
	{
		FFrame::KismetExecutionMessage(TEXT("Open Generic Widget Must Provide a Widget."), ELogVerbosity::Error);
		return;
	}

	Widget->GetOnWidgetActiveAnimationPlayFinish().AddUObject(this, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);
	if (UGenericWidgetSubsystem* GenericWidgetManager = UGenericWidgetSubsystem::Get(WorldContextObject))
	{
		GenericWidgetManager->OpenGenericWidget(Widget, FOnWidgetActiveStateChanged::CreateUObject(this, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
	}
}

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidget(UObject* InWorldContextObject, UGenericWidget* InWidget)
{
	check(InWidget);

	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->Widget = InWidget;

	return NewAction;
}

void UOpenGenericWidgetAsyncAction::OnWidgetActived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast(InWidget);
}

void UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetActiveAnimationPlayFinish().RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
