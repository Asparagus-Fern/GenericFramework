// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Style/GenericButtonStyle.h"

void UGenericButtonStyle::GetButtonStyle(FButtonStyle& OutStyle) const
{
	OutStyle
		.SetNormal(Normal)
		.SetHovered(Hovered)
		.SetPressed(Pressed)
		.SetNormalForeground(NormalForeground)
		.SetHoveredForeground(HoveredForeground)
		.SetPressedForeground(PressedForeground)
		.SetDisabledForeground(DisabledForeground)
		.SetHoveredSound(HoveredSlateSound)
		.SetPressedSound(PressedSlateSound)
		.SetNormalPadding(NormalPadding)
		.SetPressedPadding(PressedPadding);
}
