// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Components/DynamicEntryBox.h"
#include "GeneraicDynamicEntryBox.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCommonRadialBoxSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 360), Category="RadialBox Settings")
	float StartingAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="RadialBox Settings")
	bool bDistributeItemsEvenly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360), Category="RadialBox Settings")
	float AngleBetweenItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360), Category="RadialBox Settings")
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
class DEVSLATECORE_API UGeneraicDynamicEntryBox : public UDynamicEntryBox
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

public:
	UFUNCTION(BlueprintCallable, Category="Dynamic Entry Box")
	void AddEntry(UUserWidget* InUserWidget);

	UFUNCTION(BlueprintPure, DisplayName= "GetRadialBoxSettings", Category="Dynamic Entry Box")
	FCommonRadialBoxSettings BP_GetRadialBoxSettings() const;

	UFUNCTION(BlueprintCallable, DisplayName= "SetRadialBoxSettings", Category="Dynamic Entry Box")
	void BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings);
};
