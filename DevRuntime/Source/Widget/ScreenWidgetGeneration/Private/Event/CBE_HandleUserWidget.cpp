// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleUserWidget.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"

UUserWidgetBase* FOpenUserWidgetHandle::GetOpenWidget() const
{
	if (bInstance)
	{
		if (IsValid(Widget))
		{
			return Widget;
		}
	}
	else
	{
		if (WidgetClass)
		{
			return CreateWidget<UUserWidgetBase>(GetManager<UScreenWidgetManager>()->GetWorld(), WidgetClass);
		}
	}

	return nullptr;
}

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
			GetManager<UScreenWidgetManager>()->CloseUserWidget(CloseSlotTag);
		}
	}

	for (auto& ActiveOpenWidget : ActiveOpenWidgets)
	{
		UUserWidgetBase* OpenWidget = ActiveOpenWidget.GetOpenWidget();
		if (IsValid(OpenWidget))
		{
			GetManager<UScreenWidgetManager>()->OpenUserWidget(OpenWidget);
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
			GetManager<UScreenWidgetManager>()->CloseUserWidget(CloseSlotTag);
		}
	}

	for (auto& ActiveOpenWidget : InactiveOpenWidgets)
	{
		UUserWidgetBase* OpenWidget = ActiveOpenWidget.GetOpenWidget();
		if (IsValid(OpenWidget))
		{
			GetManager<UScreenWidgetManager>()->OpenUserWidget(OpenWidget);
		}
	}
}
