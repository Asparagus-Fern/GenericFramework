// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleLevelStreaming.generated.h"

UENUM(BlueprintType)
enum class EHandleLevelStreamingMethod : uint8
{
	UseLoad,
	UseVisible
};

/**
 * 处理流关卡的切换
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleLevelStreaming : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UCBE_HandleLevelStreaming();

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHandleLevelStreamingMethod HandleLevelStreamingMethod = EHandleLevelStreamingMethod::UseVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "HandleLevelStreamingMethod==EHandleLevelStreamingMethod::UseLoad"))
	bool bLoad = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "HandleLevelStreamingMethod==EHandleLevelStreamingMethod::UseVisible"))
	bool bVisible = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> Levels;

protected:
	void OnHandleLevelsFinish();
};
