// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_CloseUserWidget.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"

void UCBE_CloseUserWidget::NativeOnActived()
{
	Super::NativeOnActived();

	if (SlotTag.IsValid())
	{
		// FSimpleMulticastDelegate OnFinish;
		// OnFinish.AddUObject(this, &UCBE_CloseUserWidget::OnCloseFinish);
		GetManager<UScreenWidgetManager>()->CloseUserWidget(SlotTag);
	}
}

void UCBE_CloseUserWidget::NativeOnInactived()
{
	Super::NativeOnInactived();
	// RequestInactivateFinish();
}

void UCBE_CloseUserWidget::OnCloseFinish()
{
	RequestActivateFinish();
}
