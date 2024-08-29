// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class WORLDWIDGETEDGENERATION_API SWorldWidgetContainer : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnWorldWidgetDoubleClicked, TSharedPtr<SWorldWidgetContainer>);

public:
	SLATE_BEGIN_ARGS(SWorldWidgetContainer)
		{
		}

		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_EVENT(FOnWorldWidgetDoubleClicked, OnWorldWidgetDoubleClicked)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

public:
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	FOnWorldWidgetDoubleClicked OnWorldWidgetDoubleClicked;
};
