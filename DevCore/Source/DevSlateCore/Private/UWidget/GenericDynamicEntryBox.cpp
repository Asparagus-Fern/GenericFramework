// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GenericDynamicEntryBox.h"

void UGenericDynamicEntryBox::AddEntry(UUserWidget* InUserWidget)
{
	AddEntryChild(*InUserWidget);
}

FCommonRadialBoxSettings UGenericDynamicEntryBox::BP_GetRadialBoxSettings() const
{
	return ConvToCommonRadialBoxSettings(GetRadialBoxSettings());
}

void UGenericDynamicEntryBox::BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	SetRadialSettings(ConvToRadialBoxSettings(InCommonRadialBoxSettings));
}
