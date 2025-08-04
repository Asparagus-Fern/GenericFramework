// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/OpenGenericWidgetAsyncAction.h"

#include "GenericWidgetManager.h"

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidget(UGenericWidget* InWidget)
{
	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();

	UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);
	OpenGenericWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));

	return NewAction;
}

UOpenGenericWidgetAsyncAction* UOpenGenericWidgetAsyncAction::AsyncOpenGenericWidgetByClass(UObject* WorldContextObject, TSubclassOf<class UGenericWidget> InWidgetClass, APlayerController* OwningPlayer)
{
	UOpenGenericWidgetAsyncAction* NewAction = NewObject<UOpenGenericWidgetAsyncAction>();

	if (InWidgetClass == nullptr)
	{
		return nullptr;
	}

	UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish);

	if (OwningPlayer)
	{
		NewAction->Widget = OpenGenericWidget<UGenericWidget>(OwningPlayer, InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
	}
	else if (APlayerController* ImpliedOwningPlayer = Cast<APlayerController>(WorldContextObject))
	{
		NewAction->Widget = OpenGenericWidget<UGenericWidget>(ImpliedOwningPlayer, InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
	}
	else if (UUserWidget* OwningWidget = Cast<UUserWidget>(WorldContextObject))
	{
		NewAction->Widget = OpenGenericWidget<UGenericWidget>(OwningWidget, InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
	}
	else if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		NewAction->Widget = OpenGenericWidget<UGenericWidget>(World, InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenGenericWidgetAsyncAction::OnWidgetActived));
	}
	else
	{
		UGenericWidgetManager::Delegate_PostWidgetOpened.RemoveAll(NewAction);
	}

	return NewAction;
}

void UOpenGenericWidgetAsyncAction::OnWidgetActived(UGenericWidget* InWidget)
{
	if (Widget == InWidget)
	{
		OnFinish.Broadcast(InWidget);
	}
}

void UOpenGenericWidgetAsyncAction::OnWidgetActivedAnimationFinish(UGenericWidget* InWidget)
{
	if (Widget == InWidget)
	{
		UGenericWidgetManager::Delegate_PostWidgetOpened.RemoveAll(this);
		OnAnimationFinish.Broadcast();
	}
}
