// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/Override/DDynamicEntryBox.h"

void UDDynamicEntryBox::AddEntry(UUserWidget* InUserWidget)
{
	AddEntryChild(*InUserWidget);
}

FCommonRadialBoxSettings UDDynamicEntryBox::BP_GetRadialBoxSettings() const
{
	return ConvToCommonRadialBoxSettings(GetRadialBoxSettings());
}

void UDDynamicEntryBox::BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	SetRadialSettings(ConvToRadialBoxSettings(InCommonRadialBoxSettings));
}
