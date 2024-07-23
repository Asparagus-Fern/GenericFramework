// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleLevelStreaming.generated.h"

/**
 * 处理流关卡的切换
 * OnCreated / OnDestroy 表示在按钮被创建或清除时调用，与激活状态无关，仅调用一次，适用于子按钮拥有一个公共的关卡
 * OnActived / OnInactived 表示在按钮激活或不激活时调用
 */
UCLASS()
class LEVELSTREAMING_API UCBE_HandleLevelStreaming : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OnActived")
	TArray<TSoftObjectPtr<UWorld>> ActivateVisibleLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OnActived")
	TArray<TSoftObjectPtr<UWorld>> ActivateHiddenLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OnInactived")
	TArray<TSoftObjectPtr<UWorld>> InactivateVisibleLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OnInactived")
	TArray<TSoftObjectPtr<UWorld>> InactivateHiddenLevels;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
	virtual bool GetIsAsync() override { return true; }

public:
	UFUNCTION()
	void OnActivateVisibleLevelsFinish();

	UFUNCTION()
	void OnActivateHiddenLevelsFinish();

	UFUNCTION()
	void OnInactivateVisibleLevelsFinish();

	UFUNCTION()
	void OnInactivateHiddenLevelsFinish();
};
