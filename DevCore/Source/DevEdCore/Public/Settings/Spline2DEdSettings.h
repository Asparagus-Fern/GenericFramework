// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Settings/GenericEdSettings.h"
#include "Spline2DEdSettings.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API USpline2DEdSettings : public UGenericEdSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Spline 2D")); }

public:
	UPROPERTY(config, EditAnywhere, Category = "UMGSpline")
	float PanelHeight = 600.0f;
};
