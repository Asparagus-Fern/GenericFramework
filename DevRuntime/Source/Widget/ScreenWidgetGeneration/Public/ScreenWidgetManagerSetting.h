// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "ScreenWidgetManagerSetting.generated.h"

class UGameMenuSetting;
class UGameHUD;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	/* 在世界开始时，将GameHUDClasses创建到屏幕 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Game HUD")
	bool AutoCreateGameHUD = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes", Category="Game HUD")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;

public:
	/* 在世界开始时，创建DefaultGameMenuSetting菜单 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Menu")
	bool AutoCreateMenu = false;

	/* 默认的菜单设置 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Menu", meta=(EditConditionHides, EditCondition = "AutoCreateMenu"))
	TSoftObjectPtr<UGameMenuSetting> DefaultGameMenuSetting;

	/* 接管菜单的处理 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Menu")
	bool ProcessingMenuSelection = true;
};
