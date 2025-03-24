// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlow_Load.h"
#include "ProcedureFlow_LoadLevelStreaming.generated.h"

UCLASS(MinimalAPI)
class AProcedureFlow_LoadLevelStreaming : public AProcedureFlow_Load
{
	GENERATED_BODY()

public:
	AProcedureFlow_LoadLevelStreaming();

protected:
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;

public:
	/* 是否加载当前世界所有关卡 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoadCurrentWorldLevels = true;

	/* 需要显示的关卡 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> VisibleLevels;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadCurrentWorldLevelStreamingOnceFinish();
	void NativeOnLoadCurrentWorldLevelStreamingOnceFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadCurrentWorldLevelStreamingFinish();
	void NativeOnLoadCurrentWorldLevelStreamingFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadVisibleLevelsOnceFinish();
	void NativeOnLoadVisibleLevelsOnceFinish();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadVisibleLevelsFinish();
	void NativeOnLoadVisibleLevelsFinish();

protected:
	virtual int32 GetLoadingNum_Implementation() override;
};
