// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidget/SGenericButton.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGenericButton::Construct(const FArguments& InArgs)
{
	OnDoubleClicked = InArgs._OnDoubleClicked;

	SButton::Construct(SButton::FArguments()
		.ButtonStyle(InArgs._ButtonStyle)
		.HAlign(InArgs._HAlign)
		.VAlign(InArgs._VAlign)
		.ClickMethod(InArgs._ClickMethod)
		.TouchMethod(InArgs._TouchMethod)
		.PressMethod(InArgs._PressMethod)
		.OnClicked(InArgs._OnClicked)
		.OnPressed(InArgs._OnPressed)
		.OnReleased(InArgs._OnReleased)
		.IsFocusable(InArgs._IsFocusable)
		.Content()
		[
			InArgs._Content.Widget
		]
	);

	SetCanTick(false);

	// Set the hover state to indicate that we want to override the default behavior
	// SetHover(false);

	OnReceivedFocus = InArgs._OnReceivedFocus;
	OnLostFocus = InArgs._OnLostFocus;
	bIsButtonActived = InArgs._IsButtonActived;
	// bIsButtonEnabled = InArgs._IsButtonEnabled;
	// bIsInteractionEnabled = InArgs._IsInteractionEnabled;
	// bHovered = false;
}

void SGenericButton::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!MouseEvent.IsTouchEvent())
	{
		const bool bWasHovered = IsHovered();

		bHovered = true;
		SetHover(bHovered && bIsInteractionEnabled);
		SButton::OnMouseEnter(MyGeometry, MouseEvent);

		// SButton won't be able to correctly detect hover changes since we manually set hover, do our own detection
		if (!bWasHovered && IsHovered())
		{
			ExecuteHoverStateChanged(true);
		}
	}
}

FReply SGenericButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return IsInteractable() ? SButton::OnMouseButtonDown(MyGeometry, MouseEvent) : FReply::Handled();
}

FReply SGenericButton::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Handled();
	if (!IsInteractable())
	{
		if (HasMouseCapture())
		{
			// It's conceivable that interaction was disabled while this button had mouse capture
			// If that's the case, we want to release it (without acknowledging the click)
			Release();
			Reply.ReleaseMouseCapture();
		}
	}
	else
	{
		Reply = SButton::OnMouseButtonUp(MyGeometry, MouseEvent);
	}

	return Reply;
}

bool SGenericButton::IsInteractable() const
{
	return bIsButtonActived;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
