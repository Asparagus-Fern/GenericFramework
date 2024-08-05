// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/CommonDynamicEntryBox.h"

void UCommonDynamicEntryBox::AddEntry(UUserWidget* InUserWidget)
{
	AddEntryChild(*InUserWidget);
}

FCommonRadialBoxSettings UCommonDynamicEntryBox::BP_GetRadialBoxSettings() const
{
	return ConvertToCommonRadialBoxSettings(GetRadialBoxSettings());
}

void UCommonDynamicEntryBox::BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	SetRadialSettings(ConvertToRadialBoxSettings(InCommonRadialBoxSettings));
}
