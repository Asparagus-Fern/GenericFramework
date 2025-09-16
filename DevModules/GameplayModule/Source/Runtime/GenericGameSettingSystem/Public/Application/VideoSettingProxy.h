// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyProxy.h"
#include "VideoSettingProxy.generated.h"

class USinglePropertyValueViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UVideoSettingProxy : public UPropertyProxy
{
	GENERATED_BODY()

public:
	GENERICGAMESETTINGSYSTEM_API virtual void GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result) override;
};
