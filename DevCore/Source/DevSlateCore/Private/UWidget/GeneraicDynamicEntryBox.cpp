// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GeneraicDynamicEntryBox.h"

void UGeneraicDynamicEntryBox::AddEntry(UUserWidget* InUserWidget)
{
	AddEntryChild(*InUserWidget);
}

FCommonRadialBoxSettings UGeneraicDynamicEntryBox::BP_GetRadialBoxSettings() const
{
	return ConvToCommonRadialBoxSettings(GetRadialBoxSettings());
}

void UGeneraicDynamicEntryBox::BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	SetRadialSettings(ConvToRadialBoxSettings(InCommonRadialBoxSettings));
}
