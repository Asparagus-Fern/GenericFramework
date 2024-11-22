// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Components/DynamicEntryBox.h"
#include "DDynamicEntryBox.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCommonRadialBoxSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 360))
	float StartingAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDistributeItemsEvenly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
	float AngleBetweenItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
	float SectorCentralAngle;

	FCommonRadialBoxSettings()
		: StartingAngle(0.f)
		  , bDistributeItemsEvenly(true)
		  , AngleBetweenItems(0.f)
		  , SectorCentralAngle(360.f)
	{
	}

	FCommonRadialBoxSettings(const float InStartingAngle, const bool InDistributeItemsEvenly, const float InAngleBetweenItems, const float InSectorCentralAngle)
		: StartingAngle(InStartingAngle)
		  , bDistributeItemsEvenly(InDistributeItemsEvenly)
		  , AngleBetweenItems(InAngleBetweenItems)
		  , SectorCentralAngle(InSectorCentralAngle)
	{
	}
};

static FRadialBoxSettings ConvToRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	FRadialBoxSettings RadialBoxSettings;
	RadialBoxSettings.StartingAngle = InCommonRadialBoxSettings.StartingAngle;
	RadialBoxSettings.AngleBetweenItems = InCommonRadialBoxSettings.AngleBetweenItems;
	RadialBoxSettings.bDistributeItemsEvenly = InCommonRadialBoxSettings.bDistributeItemsEvenly;
	RadialBoxSettings.SectorCentralAngle = InCommonRadialBoxSettings.SectorCentralAngle;

	return RadialBoxSettings;
}

static FCommonRadialBoxSettings ConvToCommonRadialBoxSettings(FRadialBoxSettings InRadialBoxSettings)
{
	FCommonRadialBoxSettings CommonRadialBoxSettings;
	CommonRadialBoxSettings.StartingAngle = InRadialBoxSettings.StartingAngle;
	CommonRadialBoxSettings.AngleBetweenItems = InRadialBoxSettings.AngleBetweenItems;
	CommonRadialBoxSettings.bDistributeItemsEvenly = InRadialBoxSettings.bDistributeItemsEvenly;
	CommonRadialBoxSettings.SectorCentralAngle = InRadialBoxSettings.SectorCentralAngle;

	return CommonRadialBoxSettings;
}

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UDDynamicEntryBox : public UDynamicEntryBox
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
