// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSetting.h"
#include "WidgetGenerationSetting.generated.h"

class UGameHUD;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UWidgetGenerationSetting : public UGenericSetting
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Widget")); }

	/* HUD */
public:
	/* 在世界开始时，将GameHUDClasses创建到屏幕 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="HUD")
	bool AutoCreateGameHUD = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes", Category="HUD")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;
};
