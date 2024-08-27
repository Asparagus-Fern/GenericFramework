// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/DynamicPositionBox.h"

#include "ScreenWidgetManager.h"
#include "Components/CanvasPanel.h"

void UDynamicPositionBox::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(CanvasPanel))
	{
		CanvasPanel->ClearChildren();

		for (auto& CanvasPanelWidget : CanvasPanelWidgets)
		{
			if (IsDesignTime())
			{
				if (IsValid(CanvasPanelWidget.WidgetContainer.WidgetClass))
				{
					UUserWidget* Widget = CreateWidget<UUserWidgetBase>(this, CanvasPanelWidget.WidgetContainer.WidgetClass);
					UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(Widget);
					CanvasPanelSlot->SetLayout(CanvasPanelWidget.LayoutData);
					CanvasPanelSlot->SetAutoSize(CanvasPanelWidget.bAutoSize);
					CanvasPanelSlot->SetZOrder(CanvasPanelWidget.ZOrder);
					CanvasPanelSlot->SetPosition(CanvasPanelWidget.Position);
				}
			}
			else
			{
				UUserWidgetBase* ContainerWidget = UScreenWidgetManager::GetContainerWidget(CanvasPanelWidget.WidgetContainer);
				if (IsValid(ContainerWidget))
				{
					UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(ContainerWidget);
					CanvasPanelSlot->SetLayout(CanvasPanelWidget.LayoutData);
					CanvasPanelSlot->SetAutoSize(CanvasPanelWidget.bAutoSize);
					CanvasPanelSlot->SetZOrder(CanvasPanelWidget.ZOrder);
					CanvasPanelSlot->SetPosition(CanvasPanelWidget.Position);
				}
			}
		}
	}
}
