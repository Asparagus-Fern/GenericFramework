// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generaic/GenericEdSetting.h"
#include "UMGEdSetting.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UUMGEdSetting : public UGenericEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("UMG Editor")); }

public:
	UPROPERTY(config, EditAnywhere, Category = "UMGSpline")
	float PanelHeight = 600.0f;
};
