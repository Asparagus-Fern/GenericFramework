// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "ScreenWidgetManagerSetting.generated.h"

class UShortcutWidgetBinding;
class UUserWidgetBase;
class UInputAction;
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
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	bool AutoCreateGameHUD = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;

	/* Widget的快捷操作(ex:快捷键打开Widget) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UShortcutWidgetBinding> ShortcutWidgetBinding;
};
