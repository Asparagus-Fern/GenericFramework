// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_OpenUserWidget.generated.h"

/**
 * 打开一个Widget
 */
UCLASS(MinimalAPI)
class UCBE_OpenUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWidgetContainer> OpenWidgets;

protected:
	int32 OpenWidgetIndex = 0;
	TArray<UUserWidgetBase*> GetValidWidgets();
};
