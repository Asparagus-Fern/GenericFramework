// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyDetailDescriptionPanel.generated.h"

class UPropertyCollection;

/**
 * 属性详细描述面板
 */
UCLASS(MinimalAPI)
class UPropertyDetailDescriptionPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API void UpdatePropertyDetailDescription(UPropertyCollection* InPropertyCollection);
};
