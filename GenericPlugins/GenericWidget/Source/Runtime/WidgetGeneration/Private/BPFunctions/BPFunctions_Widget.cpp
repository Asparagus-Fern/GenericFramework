// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"


TArray<UGenericWidget*> UBPFunctions_Widget::GetActivedWidgets(const UObject* WorldContextObject)
{
	if (UGenericWidgetSubsystem* WidgetManager = UGenericWidgetSubsystem::Get(WorldContextObject))
	{
		return WidgetManager->GetActivedWidgets();
	}
	return TArray<UGenericWidget*>{};
}
