// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/CloseGenericWidgetAsyncAction.h"

#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidget(UGenericWidget* InWidget, const bool MarkAsGarbage)
{
	UCloseGenericWidgetAsyncAction* NewAction = NewObject<UCloseGenericWidgetAsyncAction>();

	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(NewAction, &UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
	CloseGenericWidget(InWidget, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseGenericWidgetAsyncAction::OnWidgetInactived));

	return NewAction;
}

UCloseGenericWidgetAsyncAction* UCloseGenericWidgetAsyncAction::AsyncCloseGenericWidgetByTag(const FGameplayTag InSlotTag, const bool MarkAsGarbage)
{
	UCloseGenericWidgetAsyncAction* NewAction = NewObject<UCloseGenericWidgetAsyncAction>();

	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(NewAction, &UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
	CloseGenericWidget(InSlotTag, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseGenericWidgetAsyncAction::OnWidgetInactived));

	return NewAction;
}

void UCloseGenericWidgetAsyncAction::OnWidgetInactived(UGenericWidget* InWidget)
{
	OnFinish.Broadcast();
}

void UCloseGenericWidgetAsyncAction::OnWidgetInactivedAnimationFinish(UGenericWidget* InWidget)
{
	UGenericWidgetManager::Delegate_PostWidgetClosed.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
