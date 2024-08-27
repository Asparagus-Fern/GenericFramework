// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimelineButtonEvent.h"
#include "TBE_HandleMaterialScalarParameter.generated.h"

/**
 * 处理材质参数集Scalar参数
 */
UCLASS()
class APPLICATIONRUNTIME_API UTBE_HandleMaterialScalarParameter : public UTimelineButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

	/* ITimelineButtonEventInterface */
public:
	virtual void HandleTimelineUpdate_Implementation(float Alpha) override;

	/* UCBE_HandleMaterialScalarParameter */
public:
	/* 参数集 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialParameterCollection* Collection;

	/* 参数集名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bIsTimeline"))
	float Value = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsTimeline"))
	float StartValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsTimeline"))
	float EndValue = 1.f;
};
