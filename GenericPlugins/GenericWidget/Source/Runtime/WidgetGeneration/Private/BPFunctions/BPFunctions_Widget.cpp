// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"


TArray<UGenericWidget*> UBPFunctions_Widget::GetActivedWidgets(const UObject* WorldContextObject)
{
	if (const UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(WorldContextObject))
	{
		return GenericWidgetSubsystem->GetActivedWidgets();
	}
	return TArray<UGenericWidget*>{};
}

UGenericWidget* UBPFunctions_Widget::GetActivedWidget(const UObject* WorldContextObject, TSubclassOf<UGenericWidget> InClass, FGameplayTag InTag)
{
	ensureAlways(InClass);
	if (const UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(WorldContextObject))
	{
		return GenericWidgetSubsystem->GetActivedWidget(InTag);
	}
	return nullptr;
}
