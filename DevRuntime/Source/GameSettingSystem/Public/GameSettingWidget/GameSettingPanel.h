// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "GameSettingPanel.generated.h"

class UGameMenuSetting;

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettingPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGameMenuSetting> GameMenuSetting = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UGameMenuSetting> PreviewGameMenuSetting = nullptr;
};
