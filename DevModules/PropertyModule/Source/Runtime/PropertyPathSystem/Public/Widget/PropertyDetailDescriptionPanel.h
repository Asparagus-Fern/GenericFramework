// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "PropertyDetailDescriptionPanel.generated.h"

class UPropertyCollection;

/**
 * 属性详细描述面板
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDetailDescriptionPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void UpdatePropertyDetailDescription(UPropertyCollection* InPropertyCollection);
};
