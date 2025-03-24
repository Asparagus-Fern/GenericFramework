// Copyright ChenTaiye 2025. All Rights Reserved.


#include "SEditorWorldWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEditorWorldWidget::Construct(const FArguments& InArgs)
{
	OnWorldWidgetMiddleClicked = InArgs._OnWorldWidgetMiddleClicked;

	ChildSlot
	[
		InArgs._Content.Widget
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
