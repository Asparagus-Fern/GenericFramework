// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CommonDynamicEntryBox.h"

void UCommonDynamicEntryBox::AddEntry(UUserWidget* InUserWidget)
{
	AddEntryChild(*InUserWidget);
}

FCommonRadialBoxSettings UCommonDynamicEntryBox::BP_GetRadialBoxSettings() const
{
	const FRadialBoxSettings FoundRadialBoxSettings = GetRadialBoxSettings();
	const FCommonRadialBoxSettings CommonRadialBoxSettings(FoundRadialBoxSettings.StartingAngle, FoundRadialBoxSettings.bDistributeItemsEvenly, FoundRadialBoxSettings.AngleBetweenItems, FoundRadialBoxSettings.SectorCentralAngle);
	return CommonRadialBoxSettings;
}

void UCommonDynamicEntryBox::BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	FRadialBoxSettings NewRadialBoxSettings;
	NewRadialBoxSettings.StartingAngle = InCommonRadialBoxSettings.StartingAngle;
	NewRadialBoxSettings.AngleBetweenItems = InCommonRadialBoxSettings.AngleBetweenItems;
	NewRadialBoxSettings.bDistributeItemsEvenly = InCommonRadialBoxSettings.bDistributeItemsEvenly;
	NewRadialBoxSettings.SectorCentralAngle = InCommonRadialBoxSettings.SectorCentralAngle;

	SetRadialSettings(NewRadialBoxSettings);
}
