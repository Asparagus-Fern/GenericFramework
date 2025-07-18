// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/CloseUserWidgetAsyncAction.h"

#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidget(UGenericWidget* InWidget, const bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
		WidgetManager->CloseUserWidget(InWidget, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactived));
	}

	return NewAction;
}

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidgetByTag(const FGameplayTag InSlotTag, const bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
		WidgetManager->CloseUserWidget(InSlotTag, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactived));
	}

	return NewAction;
}

void UCloseUserWidgetAsyncAction::OnWidgetInactived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast();
}

void UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish(UGenericWidget* InWidget)
{
	UGenericWidgetManager::Delegate_PostWidgetClosed.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
