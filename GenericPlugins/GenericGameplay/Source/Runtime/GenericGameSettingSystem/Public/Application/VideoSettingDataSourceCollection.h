// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameSettingDataSourceCollection.h"
#include "VideoSettingDataSourceCollection.generated.h"

class USinglePropertyValueViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UVideoSettingDataSourceCollection : public UGameSettingDataSourceCollection
{
	GENERATED_BODY()

public:
	GENERICGAMESETTINGSYSTEM_API virtual void GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result) override;
};
