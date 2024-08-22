// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleUserWidget.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"

FGameplayTag FCloseUserWidgetHandle::GetCloseWidgetSlotTag() const
{
	if (SlotTag.IsValid())
	{
		return SlotTag;
	}
	else if (IsValid(CloseWidgetClass))
	{
		const UUserWidgetBase* UserWidgetBase = Cast<UUserWidgetBase>(CloseWidgetClass->ClassDefaultObject);
		if (IsValid(UserWidgetBase))
		{
			return UserWidgetBase->SlotTag;
		}
	}

	return FGameplayTag::EmptyTag;
}

void UCBE_HandleUserWidget::NativeOnActived()
{
	Super::NativeOnActived();

	for (auto& ActiveCloseWidget : ActiveCloseWidgets)
	{
		FGameplayTag CloseSlotTag = ActiveCloseWidget.GetCloseWidgetSlotTag();
		if (CloseSlotTag.IsValid())
		{
			// GetManager<UScreenWidgetManager>()->CloseUserWidget(CloseSlotTag);
		}
	}

	for (auto& ActiveOpenWidget : ActiveOpenWidgets)
	{
		UUserWidgetBase* OpenWidget = ActiveOpenWidget.GetWidget();
		if (IsValid(OpenWidget))
		{
			// GetManager<UScreenWidgetManager>()->OpenUserWidget(OpenWidget);
		}
	}
}

void UCBE_HandleUserWidget::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (auto& ActiveCloseWidget : InactiveCloseWidgets)
	{
		FGameplayTag CloseSlotTag = ActiveCloseWidget.GetCloseWidgetSlotTag();
		if (CloseSlotTag.IsValid())
		{
			// GetManager<UScreenWidgetManager>()->CloseUserWidget(CloseSlotTag);
		}
	}

	for (auto& ActiveOpenWidget : InactiveOpenWidgets)
	{
		UUserWidgetBase* OpenWidget = ActiveOpenWidget.GetWidget();
		if (IsValid(OpenWidget))
		{
			// GetManager<UScreenWidgetManager>()->OpenUserWidget(OpenWidget);
		}
	}
}
