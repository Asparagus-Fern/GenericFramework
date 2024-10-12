// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/PropertyPanel.h"
#include "GameSettingPanel.generated.h"

class UTextBlock;
class UGameMenuSetting;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UGameSettingPanel : public UPropertyPanel
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void OnSettingMenuSelectionChanged(UObject* InObject);
	virtual void RefreshPropertyWidget() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Setting;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_SettingDescription;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyListView> ListView_SettingMenu;
};
