// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/UserWidgetBase.h"
#include "Manager/ManagerStatics.h"

UUserWidgetBase* UBPFunctions_Widget::OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		ensure(InWidgetClass);
		return Cast<UUserWidgetBase>(WidgetManager->OpenUserWidget(InWidgetClass));
	}
	return nullptr;
}

bool UBPFunctions_Widget::OpenUserWidget(UUserWidgetBase* InWidget)
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		return WidgetManager->OpenUserWidget(InWidget);
	}
	return false;
}

bool UBPFunctions_Widget::CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage)
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		return WidgetManager->CloseUserWidget(InSlotTag, MarkAsGarbage);
	}
	return false;
}

bool UBPFunctions_Widget::CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage)
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		return WidgetManager->CloseUserWidget(InWidget, MarkAsGarbage);
	}
	return false;
}

TArray<UUserWidgetBase*> UBPFunctions_Widget::GetActivedWidgets()
{
	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		return WidgetManager->GetActivedWidgets();
	}
	return TArray<UUserWidgetBase*>{};
}
