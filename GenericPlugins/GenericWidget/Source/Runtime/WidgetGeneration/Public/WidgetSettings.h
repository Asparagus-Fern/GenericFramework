// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Settings/GenericSettings.h"
#include "WidgetSettings.generated.h"

class UGenericWidget;
class UGenericGameHUD;

/**
 * 
 */
UCLASS()
class UWidgetSettings : public UGenericSettings
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	/* If True, Will Create Game HUD After World Begin Play */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="HUD")
	bool AutoCreateGameHUD = true;

	/* The Game HUD Which Need To Auto Created */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes", Category="HUD")
	TArray<TSoftClassPtr<UGenericGameHUD>> GenericHUDClasses;

public:
	/* The Widget Which Need To Auto Created After Game HUD Created */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Widget")
	TArray<TSoftClassPtr<UGenericWidget>> WidgetClasses;
};
