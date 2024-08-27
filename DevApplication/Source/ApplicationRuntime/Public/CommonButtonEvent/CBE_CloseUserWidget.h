// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_CloseUserWidget.generated.h"

/**
 * 关闭一个Widget
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_CloseUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="HUD"))
	TArray<FGameplayTag> SlotTags;

protected:
	int32 CloseWidgetIndex = 0;
	TArray<FGameplayTag> GetValidSlotTags();
};
