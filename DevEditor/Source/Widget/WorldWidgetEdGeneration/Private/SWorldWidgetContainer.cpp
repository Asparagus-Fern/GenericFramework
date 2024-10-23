// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldWidgetContainer.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWorldWidgetContainer::Construct(const FArguments& InArgs)
{
	OnWorldWidgetDoubleClicked = InArgs._OnWorldWidgetDoubleClicked;

	ChildSlot
	[
		InArgs._Content.Widget
	];
}

FReply SWorldWidgetContainer::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	OnWorldWidgetDoubleClicked.ExecuteIfBound(SharedThis(this));
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
