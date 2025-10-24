// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameSettingProxy.h"
#include "GraphicsSettingProxy.generated.h"

class USinglePropertyValueViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGraphicsSettingProxy : public UGameSettingProxy
{
	GENERATED_BODY()

public:
	GENERICGAMESETTINGSYSTEM_API virtual void GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result) override;
};
