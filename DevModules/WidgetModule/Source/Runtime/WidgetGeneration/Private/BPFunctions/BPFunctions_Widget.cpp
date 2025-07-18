// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"
#include "Manager/ManagerStatics.h"

UGenericWidget* UBPFunctions_Widget::OpenUserWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass)
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		ensure(InWidgetClass);
		return Cast<UGenericWidget>(WidgetManager->OpenUserWidget(InWidgetClass));
	}
	return nullptr;
}

bool UBPFunctions_Widget::OpenUserWidget(UGenericWidget* InWidget)
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->OpenUserWidget(InWidget);
	}
	return false;
}

bool UBPFunctions_Widget::CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage)
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->CloseUserWidget(InSlotTag, MarkAsGarbage);
	}
	return false;
}

bool UBPFunctions_Widget::CloseUserWidget(UGenericWidget* InWidget, bool MarkAsGarbage)
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->CloseUserWidget(InWidget, MarkAsGarbage);
	}
	return false;
}

TArray<UGenericWidget*> UBPFunctions_Widget::GetActivedWidgets()
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->GetActivedWidgets();
	}
	return TArray<UGenericWidget*>{};
}
