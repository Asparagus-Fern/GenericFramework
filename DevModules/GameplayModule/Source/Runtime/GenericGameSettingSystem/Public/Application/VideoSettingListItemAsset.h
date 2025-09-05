// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListItemAsset.h"
#include "VideoSettingListItemAsset.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UVideoSettingListItemAsset : public UPropertyListItemAsset
{
	GENERATED_BODY()

protected:
	GENERICGAMESETTINGSYSTEM_API virtual void GeneratePropertyListItemObjects(TArray<UPropertyListItemObject*>& Result) override;

protected:
	GENERICGAMESETTINGSYSTEM_API virtual TMap<FName, FText> GetDisplayModeOptions();
	GENERICGAMESETTINGSYSTEM_API virtual TMap<FName, FText> GetQualityOptions();
};
