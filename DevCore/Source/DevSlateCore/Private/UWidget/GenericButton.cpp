// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/GenericButton.h"

#include "Components/ButtonSlot.h"
#include "SWidget/SGenericButton.h"

TSharedRef<SWidget> UGenericButton::RebuildWidget()
{
	MyButton = MyGenericButton = SNew(SGenericButton)
		.IsInteractionEnabled(bInteractionEnabled)
		.ClickMethod(GetClickMethod())
		.TouchMethod(GetTouchMethod())
		.PressMethod(GetPressMethod())
		.ButtonStyle(&GetStyle())
		.IsFocusable(GetIsFocusable())
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClickedOverride))
		.OnDoubleClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleDoubleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressedOverride))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleasedOverride))
		.OnReceivedFocus(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleOnReceivedFocus))
		.OnLostFocus(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleOnLostFocus));

	MyBox = SNew(SBox)
		.MinDesiredWidth(MinWidth)
		.MinDesiredHeight(MinHeight)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			MyGenericButton.ToSharedRef()
		];

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyGenericButton.ToSharedRef());
	}

	return MyBox.ToSharedRef();
}

void UGenericButton::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyGenericButton.Reset();
	MyBox.Reset();
}

void UGenericButton::SetButtonEnabled(bool bInIsButtonEnabled)
{
	bButtonEnabled = bInIsButtonEnabled;
	if (MyGenericButton.IsValid())
	{
		MyGenericButton->SetIsButtonEnabled(bInIsButtonEnabled);
	}
}

void UGenericButton::SetInteractionEnabled(bool bInIsInteractionEnabled)
{
	if (bInteractionEnabled == bInIsInteractionEnabled)
	{
		return;
	}

	bInteractionEnabled = bInIsInteractionEnabled;
	if (MyGenericButton.IsValid())
	{
		MyGenericButton->SetIsInteractionEnabled(bInIsInteractionEnabled);
	}
}

void UGenericButton::SetButtonFocusable(bool bInIsButtonFocusable)
{
	InitIsFocusable(bInIsButtonFocusable);
	if (MyGenericButton.IsValid())
	{
		MyGenericButton->SetIsButtonFocusable(bInIsButtonFocusable);
	}
}

void UGenericButton::SetMinDesiredHeight(int32 InMinHeight)
{
	MinHeight = InMinHeight;
	if (MyBox.IsValid())
	{
		MyBox->SetMinDesiredHeight(InMinHeight);
	}
}

void UGenericButton::SetMinDesiredWidth(int32 InMinWidth)
{
	MinWidth = InMinWidth;
	if (MyBox.IsValid())
	{
		MyBox->SetMinDesiredWidth(InMinWidth);
	}
}

bool UGenericButton::IsHovered() const
{
	if (MyGenericButton.IsValid())
	{
		return MyGenericButton->IsHovered();
	}
	return false;
}

bool UGenericButton::IsPressed() const
{
	if (MyGenericButton.IsValid())
	{
		return MyGenericButton->IsPressed();
	}
	return false;
}

FReply UGenericButton::SlateHandleClickedOverride()
{
	return Super::SlateHandleClicked();
}

void UGenericButton::SlateHandlePressedOverride()
{
	Super::SlateHandlePressed();
}

void UGenericButton::SlateHandleReleasedOverride()
{
	Super::SlateHandleReleased();
}

FReply UGenericButton::SlateHandleDoubleClicked()
{
	OnDoubleClicked.Broadcast();
	return FReply::Handled();
}

void UGenericButton::SlateHandleOnReceivedFocus()
{
	OnReceivedFocus.Broadcast();
}

void UGenericButton::SlateHandleOnLostFocus()
{
	OnLostFocus.Broadcast();
}
