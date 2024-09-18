// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimelineButtonEvent.h"
#include "TBE_HandleMaterialVectorParameter.generated.h"

/**
 * 处理材质参数集Vector参数
 */
UCLASS(MinimalAPI)
class UTBE_HandleMaterialVectorParameter : public UTimelineButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

	/* ITimelineButtonEventInterface */
public:
	virtual void HandleTimelineUpdate_Implementation(float Alpha) override;

	/* UCBE_HandleMaterialVectorParameter */
public:
	/* 参数集 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialParameterCollection* Collection;

	/* 参数集名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bIsTimeline"))
	FLinearColor Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsTimeline"))
	FLinearColor StartValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsTimeline"))
	FLinearColor EndValue;
};
