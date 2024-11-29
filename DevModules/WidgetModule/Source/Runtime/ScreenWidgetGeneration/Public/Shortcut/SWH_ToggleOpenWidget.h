// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShortcutWidgetHandle.h"
#include "SWH_ToggleOpenWidget.generated.h"

/**
 * 快捷键打开关闭UMG
 */
UCLASS(MinimalAPI)
class USWH_ToggleOpenWidget : public UShortcutWidgetHandle
{
	GENERATED_BODY()

protected:
	virtual void OnCompleted(const FInputActionInstance& Instance) override;
};
