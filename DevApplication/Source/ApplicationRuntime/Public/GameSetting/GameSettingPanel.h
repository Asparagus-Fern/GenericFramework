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
	virtual void SetupProperty() override;
	virtual void ClearupProperty() override;

protected:
	virtual void Refresh() override;

	virtual void OnSettingMenuSelectionChanged(UObject* InObject);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_SettingTitle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_SettingTitleDescription;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyListView> ListView_SettingMenu;
};
