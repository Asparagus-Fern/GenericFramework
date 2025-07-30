// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"
#include "Manager/ManagerStatics.h"

UGenericWidget* UBPFunctions_Widget::BP_OpenGenericWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass)
{
	return Cast<UGenericWidget>(OpenGenericWidget(InWidgetClass));
}

bool UBPFunctions_Widget::BP_OpenGenericWidget(UGenericWidget* InWidget)
{
	return OpenGenericWidget(InWidget);
}

bool UBPFunctions_Widget::BP_CloseGenericWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage)
{
	return CloseGenericWidget(InSlotTag, MarkAsGarbage);
}

bool UBPFunctions_Widget::BP_CloseGenericWidget(UGenericWidget* InWidget, bool MarkAsGarbage)
{
	return CloseGenericWidget(InWidget, MarkAsGarbage);
}

TArray<UGenericWidget*> UBPFunctions_Widget::GetActivedWidgets()
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->GetActivedWidgets();
	}
	return TArray<UGenericWidget*>{};
}
