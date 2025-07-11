// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyDetailDescriptionPanel.generated.h"

class UPropertyCollection;

/**
 * 属性详细描述面板
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDetailDescriptionPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	void UpdatePropertyDetailDescription(UPropertyCollection* InPropertyCollection);
};
