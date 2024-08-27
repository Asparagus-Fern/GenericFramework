// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleMenuSelection.generated.h"

/**
 * 处理菜单的选中状态
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleMenuSelection : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"))
	FGameplayTag TargetMenuTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TargetState = false;
};
