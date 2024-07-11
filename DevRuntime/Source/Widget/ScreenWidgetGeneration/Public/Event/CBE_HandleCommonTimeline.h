// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CommonButtonHandle.h"
#include "CBE_HandleCommonTimeline.generated.h"


/**
 * 处理时间轴类型的通用事件
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandleCommonTimeline : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 激活时触发的时间轴 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonHandle*> ActiveCommonButtonHandles;

	/* 不激活时触发的时间轴 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonHandle*> InactiveCommonButtonHandles;

protected:
	int32 ActivateIndex = 0;
	int32 InactivateIndex = 0;

	virtual TArray<UCommonButtonHandle*> GetSyncCommonButtonHandles(TArray<UCommonButtonHandle*> InCommonButtonHandles);
	virtual TArray<UCommonButtonHandle*> GetAsyncCommonButtonHandles(TArray<UCommonButtonHandle*> InCommonButtonHandles);

	virtual void OnActivateHandleOnceFinish();
	virtual void OnActivateHandleFinish();

	virtual void OnInactivateHandleOnceFinish();
	virtual void OnInactivateHandleFinish();
};
