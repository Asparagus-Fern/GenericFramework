// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlow_Load.h"
#include "ProcedureFlow_LoadLevelStreaming.generated.h"

class ULoadingPanel;
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_LoadLevelStreaming);

UCLASS()
class APPLICATIONRUNTIME_API AProcedureFlow_LoadLevelStreaming : public AProcedureFlow_Load
{
	GENERATED_BODY()

public:
	AProcedureFlow_LoadLevelStreaming();

protected:
	virtual void OnProcedureFlowEnter_Implementation(UProcedureFlowComponent* InProcedureFlow) override;
	virtual void OnProcedureFlowExit_Implementation(UProcedureFlowComponent* InProcedureFlow) override;

public:
	/* 是否加载当前世界所有关卡 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoadCurrentWorldLevels = true;

	/* 加载界面UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ULoadingPanel> LoadingClass = nullptr;

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
	
private:
	UPROPERTY(Transient)
	ULoadingPanel* LoadingUI = nullptr;
};
