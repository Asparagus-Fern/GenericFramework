// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class WORLDWIDGETEDGENERATION_API SEditorWorldWidget : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnWorldWidgetMiddleClicked, TSharedPtr<SEditorWorldWidget>);

public:
	SLATE_BEGIN_ARGS(SEditorWorldWidget)
		{
		}

		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_EVENT(FOnWorldWidgetMiddleClicked, OnWorldWidgetMiddleClicked)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

public:
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FText GetWorldWidgetTooltipText();

protected:
	FOnWorldWidgetMiddleClicked OnWorldWidgetMiddleClicked;
};
