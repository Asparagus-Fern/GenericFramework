// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HangleUserWidget.h"

#include "ScreenWidgetManager.h"

void UCBE_HangleUserWidget::NativeOnActived()
{
	Super::NativeOnActived();
	GetManager<UScreenWidgetManager>()->OpenUserWidget(HandleWidget);
}

void UCBE_HangleUserWidget::NativeOnInactived()
{
	Super::NativeOnInactived();
	GetManager<UScreenWidgetManager>()->CloseUserWidget(HandleWidget);
}
