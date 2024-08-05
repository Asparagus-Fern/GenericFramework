// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Common/UniformWidgetBox.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UUniformWidgetBox::NativePreConstruct()
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
				if (IsValid(UniformGridPanelWidget.WidgetContainer.GetWidget()))
				{
					UUniformGridSlot* UniformGridSlot = UniformGridPanel->AddChildToUniformGrid(UniformGridPanelWidget.WidgetContainer.GetWidget(), UniformGridPanelWidget.Row, UniformGridPanelWidget.Colum);
					UniformGridSlot->SetHorizontalAlignment(UniformGridPanelWidget.HorizontalAlignment);
					UniformGridSlot->SetVerticalAlignment(UniformGridPanelWidget.VerticalAlignment);
				}
			}
		}
	}
}

void UUniformWidgetBox::NativeConstruct()
{
	Super::NativeConstruct();
}
