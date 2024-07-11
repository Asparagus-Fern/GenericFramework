// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandleActorActivateState.generated.h"

/**
 * 处理设置Actor的激活状态
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandleActorActivateState : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 激活时需要处理的Actor的激活状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AActor>, bool> ActiveHandleActorState;

	/* 不激活时需要处理的Actor的激活状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AActor>, bool> InactiveHandleActorState;
};
