// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Components/DynamicEntryBox.h"
#include "CommonDynamicEntryBox.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UCommonDynamicEntryBox : public UDynamicEntryBox
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

public:
	UFUNCTION(BlueprintCallable)
	void AddEntry(UUserWidget* InUserWidget);

	UFUNCTION(BlueprintPure, DisplayName= "GetRadialBoxSettings")
	FCommonRadialBoxSettings BP_GetRadialBoxSettings() const;

	UFUNCTION(BlueprintCallable, DisplayName= "SetRadialBoxSettings")
	void BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings);
};
