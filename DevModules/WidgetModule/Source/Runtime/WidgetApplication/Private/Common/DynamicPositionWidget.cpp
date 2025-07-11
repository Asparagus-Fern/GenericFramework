// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Common/DynamicPositionWidget.h"

#include "Components/CanvasPanel.h"

void UDynamicPositionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(CanvasPanel))
	{
		CanvasPanel->ClearChildren();

		for (auto& CanvasPanelWidget : CanvasPanelWidgets)
		{
			if (IsDesignTime())
			{
				// if (IsValid(CanvasPanelWidget.WidgetContainer.WidgetClass))
				// {
				// 	UUserWidget* Widget = CreateWidget<UUserWidgetBase>(this, CanvasPanelWidget.WidgetContainer.WidgetClass);
				// 	UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(Widget);
				// 	CanvasPanelSlot->SetLayout(CanvasPanelWidget.LayoutData);
				// 	CanvasPanelSlot->SetAutoSize(CanvasPanelWidget.bAutoSize);
				// 	CanvasPanelSlot->SetZOrder(CanvasPanelWidget.ZOrder);
				// 	CanvasPanelSlot->SetPosition(CanvasPanelWidget.Position);
				// }
			}
			else
			{
				// if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
				// {
				// 	UUserWidgetBase* ContainerWidget = ScreenWidgetManager->GetContainerWidget(CanvasPanelWidget.WidgetContainer);
				// 	if (IsValid(ContainerWidget))
				// 	{
				// 		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(ContainerWidget);
				// 		CanvasPanelSlot->SetLayout(CanvasPanelWidget.LayoutData);
				// 		CanvasPanelSlot->SetAutoSize(CanvasPanelWidget.bAutoSize);
				// 		CanvasPanelSlot->SetZOrder(CanvasPanelWidget.ZOrder);
				// 		CanvasPanelSlot->SetPosition(CanvasPanelWidget.Position);
				// 	}
				// }
			}
		}
	}
}
