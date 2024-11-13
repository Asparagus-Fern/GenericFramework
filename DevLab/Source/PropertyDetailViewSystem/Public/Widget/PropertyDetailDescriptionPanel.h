// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "PropertyDetailDescriptionPanel.generated.h"

class UPropertyCollection;

/**
 * 属性详细描述面板
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDetailDescriptionPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void UpdatePropertyDetailDescription(UPropertyCollection* InPropertyCollection);
};
