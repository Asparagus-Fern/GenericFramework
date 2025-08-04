// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Widget.h"

#include "Base/GenericWidget.h"
#include "Manager/ManagerStatics.h"

UGenericWidget* UBPFunctions_Widget::BP_OpenGenericWidgetByClass(UObject* WorldContextObject, TSubclassOf<UGenericWidget> InWidgetClass, APlayerController* OwningPlayer)
{
	if (InWidgetClass == nullptr)
	{
		return nullptr;
	}

	if (OwningPlayer)
	{
		return OpenGenericWidget<UGenericWidget>(OwningPlayer, InWidgetClass);
	}
	else if (APlayerController* ImpliedOwningPlayer = Cast<APlayerController>(WorldContextObject))
	{
		return OpenGenericWidget<UGenericWidget>(ImpliedOwningPlayer, InWidgetClass);
	}
	else if (UUserWidget* OwningWidget = Cast<UUserWidget>(WorldContextObject))
	{
		return OpenGenericWidget<UGenericWidget>(OwningWidget, InWidgetClass);
	}
	else if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		return OpenGenericWidget<UGenericWidget>(World, InWidgetClass);
	}

	return nullptr;
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
