// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerEdSetting.h"
#include "WidgetEdGenerationSetting.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEDGENERATION_API UWidgetEdGenerationSetting : public UManagerEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetSectionName() const override { return "UMG"; }

public:
	UPROPERTY(EditAnywhere, config, Category = "UMGSpline")
	float PanelHeight = 600.0f;
};
