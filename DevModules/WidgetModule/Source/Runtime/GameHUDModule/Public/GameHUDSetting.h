// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "GameHUDSetting.generated.h"

class UGameHUD;

/**
 * 
 */
UCLASS()
class GAMEHUDMODULE_API UGameHUDSetting : public UManagerSetting
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetSectionName() const override { return "UMG"; }

public:
	/* 在世界开始时，将GameHUDClasses创建到屏幕 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="HUD")
	bool AutoCreateGameHUD = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes", Category="HUD")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;
};
