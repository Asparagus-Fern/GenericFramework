// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicEntryBox.h"
#include "CommonDynamicEntryBox.generated.h"

USTRUCT(BlueprintType)
struct FCommonRadialBoxSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (ClampMin = 0, ClampMax = 360))
	float StartingAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	bool bDistributeItemsEvenly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (EditCondition = "!bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
	float AngleBetweenItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (EditCondition = "bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
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

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCommonDynamicEntryBox : public UDynamicEntryBox
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

public:
	UFUNCTION(BlueprintCallable, Category = "CommonDynamicEntryBox")
	void AddEntry(UUserWidget* InUserWidget);

	UFUNCTION(BlueprintPure, DisplayName= "GetRadialBoxSettings", Category = "CommonDynamicEntryBox")
	FCommonRadialBoxSettings BP_GetRadialBoxSettings() const;

	UFUNCTION(BlueprintCallable, DisplayName= "SetRadialBoxSettings", Category = "CommonDynamicEntryBox")
	void BP_SetRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings);
};
