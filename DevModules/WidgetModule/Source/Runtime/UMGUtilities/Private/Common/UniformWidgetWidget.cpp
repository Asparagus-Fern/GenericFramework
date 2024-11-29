// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/UniformWidgetWidget.h"

#include "ScreenWidgetManager.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Manager/ManagerProxy.h"

void UUniformWidgetWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(UniformGridPanel))
	{
		UniformGridPanel->ClearChildren();
		UniformGridPanel->SetSlotPadding(SlotPadding);
		UniformGridPanel->SetMinDesiredSlotWidth(MinDesiredSlotWidth);
		UniformGridPanel->SetMinDesiredSlotHeight(MinDesiredSlotHeight);

		for (auto& UniformGridPanelWidget : UniformGridPanelWidgets)
		{
			if (IsDesignTime())
			{
				if (IsValid(UniformGridPanelWidget.WidgetContainer.WidgetClass))
				{
					UUserWidget* Widget = CreateWidget<UUserWidgetBase>(this, UniformGridPanelWidget.WidgetContainer.WidgetClass);
					UUniformGridSlot* UniformGridSlot = UniformGridPanel->AddChildToUniformGrid(Widget, UniformGridPanelWidget.Row, UniformGridPanelWidget.Colum);
					UniformGridSlot->SetHorizontalAlignment(UniformGridPanelWidget.HorizontalAlignment);
					UniformGridSlot->SetVerticalAlignment(UniformGridPanelWidget.VerticalAlignment);
				}
			}
			else
			{
				if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
				{
					UUserWidgetBase* ContainerWidget = ScreenWidgetManager->GetContainerWidget(UniformGridPanelWidget.WidgetContainer);
					if (IsValid(ContainerWidget))
					{
						UUniformGridSlot* UniformGridSlot = UniformGridPanel->AddChildToUniformGrid(ContainerWidget, UniformGridPanelWidget.Row, UniformGridPanelWidget.Colum);
						UniformGridSlot->SetHorizontalAlignment(UniformGridPanelWidget.HorizontalAlignment);
						UniformGridSlot->SetVerticalAlignment(UniformGridPanelWidget.VerticalAlignment);
					}
				}
			}
		}
	}
}

void UUniformWidgetWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
