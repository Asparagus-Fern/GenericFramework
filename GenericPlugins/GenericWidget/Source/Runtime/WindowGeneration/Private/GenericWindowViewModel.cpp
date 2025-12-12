// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowViewModel.h"

#include "Style/GenericWindowStyle.h"

TSharedRef<SWindow> UGenericWindowViewModel::GetWindow()
{
	if (UGenericWindowStyle* GenericWindowStyleCDO = GetWindowStyleCDO())
	{
		GenericWindowStyleCDO->GetWindowStyle(WindowStyle);
	}

	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.Type(ConvertToWindowType(WindowType))
		.Style(&WindowStyle)
		.Title(WindowTitle)
		.bDragAnywhere(bDragAnywhere)
		.AutoCenter(ConvertToAutoCenter(AutoCenter))
		.ScreenPosition(Position)
		.ClientSize(Size)
		.AdjustInitialSizeAndPositionForDPIScale(bAdjustInitialSizeAndPositionForDPIScale)
		// .SupportsTransparency(ConvertToWindowTransparency(Transparency))
		// .InitialOpacity(InitialOpacity)
		.IsInitiallyMaximized(IsInitiallyMaximized)
		.IsInitiallyMinimized(IsInitiallyMinimized)
		.SizingRule(ConvertToSizingRule(SizingRule))
		.IsPopupWindow(IsPopupWindow)
		.IsTopmostWindow(IsTopmostWindow)
		.FocusWhenFirstShown(bFocusWhenFirstShown)
		.ActivationPolicy(ConvertToWindowActivationPolicy(ActivationPolicy))
		.UseOSWindowBorder(bUseOSWindowBorder)
		.HasCloseButton(HasCloseButton)
		.SupportsMaximize(bSupportsMaximize)
		.SupportsMinimize(bSupportsMinimize)
		.ShouldPreserveAspectRatio(false)
		.CreateTitleBar(bCreateTitleBar)
		.SaneWindowPlacement(bSaneWindowPlacement)
		.LayoutBorder(LayoutBorder)
		.UserResizeBorder(UserResizeBorder)
		.bManualManageDPI(false)
		.CloseButtonToolTipText(CloseButtonToolTipText);

	FWindowSizeLimits SizeLimits;
	if (bClampMinWidth) { SizeLimits.SetMinWidth(MinWidth); }
	if (bClampMinHeight) { SizeLimits.SetMinHeight(MinHeight); }
	if (bClampMaxWidth) { SizeLimits.SetMaxWidth(MaxWidth); }
	if (bClampMaxHeight) { SizeLimits.SetMaxHeight(MaxHeight); }
	NewWindow->SetSizeLimits(SizeLimits);

	WindowPtr = NewWindow;
	return NewWindow;
}

UGenericWindowStyle* UGenericWindowViewModel::GetWindowStyleCDO() const
{
	if (WindowStyleClass)
	{
		if (UGenericWindowStyle* GenericWindowStyle = Cast<UGenericWindowStyle>(WindowStyleClass->ClassDefaultObject))
		{
			return GenericWindowStyle;
		}
	}
	return nullptr;
}
