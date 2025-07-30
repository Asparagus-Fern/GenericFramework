// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/OpenGenericWidgetAsyncAction.h"

#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidget(UGenericWidget* InWidget)
{
	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();

	UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);
	OpenGenericWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));

	return NewAction;
}

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass)
{
	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();

	UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);
	OpenGenericWidget(InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));

	return NewAction;
}

void UOpenGenericWidgetAsyncAction::OnWidgetActived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast(InWidget);
}

void UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish(UGenericWidget* InWidget)
{
	UGenericWidgetManager::Delegate_PostWidgetOpened.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
