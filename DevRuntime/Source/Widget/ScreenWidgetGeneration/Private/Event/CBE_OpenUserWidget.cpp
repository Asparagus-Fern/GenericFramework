// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_OpenUserWidget.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"

void UCBE_OpenUserWidget::NativeOnActived()
{
	Super::NativeOnActived();

	// FSimpleMulticastDelegate OnFinish;
	// OnFinish.AddUObject(this, &UCBE_OpenUserWidget::OnOpenFinish);
	GetManager<UScreenWidgetManager>()->OpenUserWidget(DuplicateObject(HandleWidget,HandleWidget->GetOuter()));
}

void UCBE_OpenUserWidget::NativeOnInactived()
{
	Super::NativeOnInactived();
	// RequestInactivateFinish();
}

void UCBE_OpenUserWidget::OnOpenFinish()
{
	RequestActivateFinish();
}
