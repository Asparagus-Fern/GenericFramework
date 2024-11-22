// Fill out your copyright notice in the Description page of Project Settings.

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
