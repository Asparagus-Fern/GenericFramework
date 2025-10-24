// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/OpenGenericWidgetAsyncAction.h"

#include "GenericWidgetManager.h"

void UOpenGenericWidgetAsyncAction::Activate()
{
	Super::Activate();

	if (!Widget)
	{
		FFrame::KismetExecutionMessage(TEXT("Open Generic Widget Must Provide a Widget."), ELogVerbosity::Error);
		return;
	}

	Widget->GetOnWidgetActiveAnimationPlayFinish().AddUObject(this, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);
	FWidgetHelper::OpenGenericWidget(Widget, FOnWidgetActiveStateChanged::CreateUObject(this, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
}

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidget(UGenericWidget* InWidget)
{
	check(InWidget);

	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();
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
