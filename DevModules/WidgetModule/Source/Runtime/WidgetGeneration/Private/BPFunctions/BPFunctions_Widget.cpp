// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"
#include "Manager/ManagerStatics.h"

TArray<UGenericWidget*> UBPFunctions_Widget::GetActivedWidgets()
{
	if (UGenericWidgetManager* WidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return WidgetManager->GetActivedWidgets();
	}
	return TArray<UGenericWidget*>{};
}
