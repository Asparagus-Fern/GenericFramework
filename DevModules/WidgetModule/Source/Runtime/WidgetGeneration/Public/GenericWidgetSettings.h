// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSettings.h"
#include "GenericWidgetSettings.generated.h"

class UGenericHUD;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UGenericWidgetSettings : public UGenericSettings
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("UMG")); }
#endif

	/* HUD */
public:
	/* 在世界开始时，将GameHUDClasses创建到屏幕 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="HUD")
	bool AutoCreateGameHUD = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes", Category="HUD")
	TArray<TSoftClassPtr<UGenericHUD>> GenericHUDClasses;
};
