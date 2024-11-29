// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldWidgetContainer.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWorldWidgetContainer::Construct(const FArguments& InArgs)
{
	OnWorldWidgetMiddleClicked = InArgs._OnWorldWidgetMiddleClicked;

	ChildSlot
	[
		InArgs._Content.Widget
	];
}

FReply SWorldWidgetContainer::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
	{
		OnWorldWidgetMiddleClicked.ExecuteIfBound(SharedThis(this));
	}
	
	return SCompoundWidget::OnMouseButtonDown(MyGeometry, MouseEvent);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
