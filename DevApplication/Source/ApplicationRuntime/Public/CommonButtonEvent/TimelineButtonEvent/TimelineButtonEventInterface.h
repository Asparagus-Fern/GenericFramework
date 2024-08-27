// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimelineButtonEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTimelineButtonEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class APPLICATIONRUNTIME_API ITimelineButtonEventInterface
{
	GENERATED_BODY()

public:
	/* 当时间轴更新时 */
	UFUNCTION(BlueprintNativeEvent)
	void HandleTimelineUpdate(float Alpha);

	/* 当时间轴完成时 */
	UFUNCTION(BlueprintNativeEvent)
	void HandleTimelineFinish(float Alpha);
};
