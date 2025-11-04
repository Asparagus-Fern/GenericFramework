// Copyright ChenTaiye 2025. All Rights Reserved.

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
	SetHover(false);

	OnReceivedFocus = InArgs._OnReceivedFocus;
	OnLostFocus = InArgs._OnLostFocus;
	bIsButtonEnabled = InArgs._IsButtonEnabled;
	bIsInteractionEnabled = InArgs._IsInteractionEnabled;
	bHovered = false;
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

void SGenericButton::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsTouchEvent())
	{
		if (HasMouseCapture())
		{
			Release();
		}
	}
	else
	{
		const bool bWasHovered = IsHovered();

		bHovered = false;
		SetHover(false);
		SButton::OnMouseLeave(MouseEvent);

		// SButton won't be able to correctly detect hover changes since we manually set hover, do our own detection
		if (bWasHovered && !IsHovered())
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

FReply SGenericButton::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	if (!IsInteractable())
	{
		return FReply::Handled();
	}

	if (OnDoubleClicked.IsBound())
	{
		FReply Reply = OnDoubleClicked.Execute();
		if (Reply.IsEventHandled())
		{
			return Reply;
		}
	}

	FReply Reply = OnMouseButtonDown(InMyGeometry, InMouseEvent);
	if (Reply.IsEventHandled())
	{
		return Reply;
	}

	return SButton::OnMouseButtonDoubleClick(InMyGeometry, InMouseEvent);
}

FReply SGenericButton::OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	FReply Reply = FReply::Handled();

	if (HasMouseCapture())
	{
		if (!MyGeometry.IsUnderLocation(InTouchEvent.GetScreenSpacePosition()))
		{
			Release();
			Reply.ReleaseMouseCapture();
		}
	}
	else
	{
		Reply = SButton::OnTouchMoved(MyGeometry, InTouchEvent);
	}

	return Reply;
}

FReply SGenericButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return SButton::OnKeyDown(MyGeometry, InKeyEvent);
}

FReply SGenericButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return SButton::OnKeyUp(MyGeometry, InKeyEvent);
}

FReply SGenericButton::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	FReply ReturnReply = SButton::OnFocusReceived(MyGeometry, InFocusEvent);
	OnReceivedFocus.ExecuteIfBound();

	return ReturnReply;
}

void SGenericButton::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	OnLostFocus.ExecuteIfBound();
}

int32 SGenericButton::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	bool bEnabled = bParentEnabled && bIsButtonEnabled;
	return SButton::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bEnabled);
}

bool SGenericButton::IsInteractable() const
{
	return bIsButtonEnabled && bIsInteractionEnabled;
}

void SGenericButton::SetIsButtonEnabled(bool bInIsButtonEnabled)
{
	bIsButtonEnabled = bInIsButtonEnabled;
}

void SGenericButton::SetIsInteractionEnabled(bool bInIsInteractionEnabled)
{
	if (bIsInteractionEnabled == bInIsInteractionEnabled)
	{
		return;
	}

	const bool bWasHovered = IsHovered();
	bIsInteractionEnabled = bInIsInteractionEnabled;

	const bool bIsHoveredNow = bHovered && bInIsInteractionEnabled;
	if (bWasHovered != bIsHoveredNow)
	{
		SetHover(bIsHoveredNow);
		ExecuteHoverStateChanged(false);
	}
}

void SGenericButton::SetIsButtonFocusable(bool bInIsButtonFocusable)
{
	SetIsFocusable(bInIsButtonFocusable);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
