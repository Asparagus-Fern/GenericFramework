// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_SwitchGameMenu.generated.h"

class UGameMenuSetting;

/**
 * 切换菜单数据
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_SwitchGameMenu : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameMenuSetting* GameMenuSetting;
};
