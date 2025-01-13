// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DEVSLATECORE_API SGenericButton : public SButton
{
public:
	SLATE_BEGIN_ARGS(SGenericButton)
			: _Content()
			  , _HAlign(HAlign_Fill)
			  , _VAlign(VAlign_Fill)
			  , _ClickMethod(EButtonClickMethod::DownAndUp)
			  , _TouchMethod(EButtonTouchMethod::DownAndUp)
			  , _PressMethod(EButtonPressMethod::DownAndUp)
			  , _IsFocusable(true)
			  , _IsButtonActived(true)
		{
		}

		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
		SLATE_ARGUMENT(EVerticalAlignment, VAlign)
		SLATE_EVENT(FOnClicked, OnClicked)
		SLATE_EVENT(FOnClicked, OnDoubleClicked)
		SLATE_EVENT(FSimpleDelegate, OnPressed)
		SLATE_EVENT(FSimpleDelegate, OnReleased)
		SLATE_ARGUMENT(EButtonClickMethod::Type, ClickMethod)
		SLATE_ARGUMENT(EButtonTouchMethod::Type, TouchMethod)
		SLATE_ARGUMENT(EButtonPressMethod::Type, PressMethod)
		SLATE_ARGUMENT(bool, IsFocusable)
		SLATE_EVENT(FSimpleDelegate, OnReceivedFocus)
		SLATE_EVENT(FSimpleDelegate, OnLostFocus)
		SLATE_ARGUMENT(bool, IsButtonActived)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

public:
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual bool IsInteractable() const override;

private:
	FOnClicked OnDoubleClicked;

	/** Delegate fired whenever focus is received */
	FSimpleDelegate OnReceivedFocus;

	/** Delegate fired whenever focus is lost */
	FSimpleDelegate OnLostFocus;

	/** True If Button Event Enable */
	bool bIsButtonActived = true;
};
