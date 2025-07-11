// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/OpenUserWidgetAsyncAction.h"

#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidget(UGenericWidget* InWidget)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UGenericWidgetManager* WidgetManager = GetManager<UGenericWidgetManager>())
	{
		UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish);
		WidgetManager->OpenUserWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActived));
	}

	return NewAction;
}

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UGenericWidgetManager* WidgetManager = GetManager<UGenericWidgetManager>())
	{
		UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish);
		WidgetManager->OpenUserWidget(InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActived));
	}

	return NewAction;
}

void UOpenUserWidgetAsyncAction::OnWidgetActived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast(InWidget);
}

void UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish(UGenericWidget* InWidget)
{
	UGenericWidgetManager::Delegate_PostWidgetOpened.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
