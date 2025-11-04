// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Style/GenericWindowStyle.h"

#include "Style/GenericButtonStyle.h"
#include "Style/GenericTextBlockStyle.h"

void UGenericWindowStyle::GetWindowStyle(FWindowStyle& OutWindowStyle) const
{
#if !PLATFORM_MAC
	FButtonStyle WindowMinimizeButtonStyle;
	if (IsValid(MinimizeButtonStyleClass))
	{
		if (UGenericButtonStyle* StyleCDO = Cast<UGenericButtonStyle>(MinimizeButtonStyleClass->ClassDefaultObject))
		{
			StyleCDO->GetButtonStyle(WindowMinimizeButtonStyle);
		}
	}

	FButtonStyle WindowMaximizeButtonStyle;
	if (IsValid(MaximizeButtonStyle))
	{
		if (UGenericButtonStyle* StyleCDO = Cast<UGenericButtonStyle>(MaximizeButtonStyle->ClassDefaultObject))
		{
			StyleCDO->GetButtonStyle(WindowMaximizeButtonStyle);
		}
	}

	FButtonStyle WindowRestoreButtonStyle;
	if (IsValid(RestoreButtonStyle))
	{
		if (UGenericButtonStyle* StyleCDO = Cast<UGenericButtonStyle>(RestoreButtonStyle->ClassDefaultObject))
		{
			StyleCDO->GetButtonStyle(WindowRestoreButtonStyle);
		}
	}

	FButtonStyle WindowCloseButtonStyle;
	if (IsValid(CloseButtonStyle))
	{
		if (UGenericButtonStyle* StyleCDO = Cast<UGenericButtonStyle>(CloseButtonStyle->ClassDefaultObject))
		{
			StyleCDO->GetButtonStyle(WindowCloseButtonStyle);
		}
	}
#endif

	FTextBlockStyle WindowTitleTextStyle;
	if (IsValid(TitleTextStyle))
	{
		if (UGenericTextBlockStyle* StyleCDO = Cast<UGenericTextBlockStyle>(TitleTextStyle->ClassDefaultObject))
		{
			StyleCDO->GetTextBlockStyle(WindowTitleTextStyle);
		}
	}

	OutWindowStyle
#if !PLATFORM_MAC
		.SetMinimizeButtonStyle(WindowMinimizeButtonStyle)
		.SetMaximizeButtonStyle(WindowMaximizeButtonStyle)
		.SetRestoreButtonStyle(WindowRestoreButtonStyle)
		.SetCloseButtonStyle(WindowCloseButtonStyle)
#endif
		.SetTitleTextStyle(WindowTitleTextStyle)
		.SetActiveTitleBrush(ActiveTitleBrush)
		.SetInactiveTitleBrush(InactiveTitleBrush)
		.SetFlashTitleBrush(FlashTitleBrush)
		.SetBackgroundBrush(BackgroundBrush)
		.SetBorderBrush(BorderBrush)
		.SetOutlineBrush(OutlineBrush)
		.SetChildBackgroundBrush(ChildBackgroundBrush)
		.SetCornerRadius(CornerRadius)
		.SetBorderPadding(BorderPadding);
}
