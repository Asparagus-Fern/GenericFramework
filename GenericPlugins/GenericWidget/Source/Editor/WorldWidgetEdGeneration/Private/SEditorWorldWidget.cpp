// Copyright ChenTaiye 2025. All Rights Reserved.

#include "SEditorWorldWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEditorWorldWidget::Construct(const FArguments& InArgs)
{
	OnWorldWidgetMiddleClicked = InArgs._OnWorldWidgetMiddleClicked;

	TSharedRef<SWidget> ContentWidget = InArgs._Content.Widget;
	ContentWidget->SetToolTipText(GetWorldWidgetTooltipText());

	ChildSlot
	[
		ContentWidget
	];
}

FReply SEditorWorldWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
	{
		OnWorldWidgetMiddleClicked.ExecuteIfBound(SharedThis(this));
	}

	return SCompoundWidget::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FText SEditorWorldWidget::GetWorldWidgetTooltipText()
{
	return FText::FromString("Middle Click To Select This Actor.");
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
