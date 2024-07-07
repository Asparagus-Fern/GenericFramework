// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Procedure/GameplayProcedure.h"
#include "ProcedureLoading.generated.h"

class UUserWidgetBase;
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureLoading_Default);

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UProcedureLoading : public UGameplayProcedure
{
	GENERATED_BODY()

public:
	UProcedureLoading();
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 下一个流程的Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	FGameplayTag NextProcedureTag;

	/* 是否有加载界面UMG */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loading UMG")
	bool bActiveLoadingWidget = true;

	/* 查找LoadingWidgets中的SelfTag来打开对应的UMG */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="UMG", EditConditionHides, EditCondition="bActiveLoadingWidget"), Category="Loading UMG")
	FGameplayTag DefaultLoadingTag;

	/* 加载界面UMG列表 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(Categories="UMG", EditConditionHides, EditCondition="bActiveLoadingWidget"), Category="Loading UMG")
	TArray<UUserWidgetBase*> LoadingWidgets;

	/* 是否为大世界 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loading World")
	bool bIsWorldPartition = false;

	/* 是否加载关卡流，为true则将接管关卡的流送 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition="!bIsWorldPartition"), Category="Loading World")
	bool bIsLoadLevelStreaming = true;

	/* 是否自动加载当前世界的所有关卡流，以便在后续显示隐藏关卡中更快 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition="!bIsWorldPartition && bIsLoadLevelStreaming"), Category="Loading World")
	bool bIsAutoLoadAllLevelStreaming = true;

	/* 需要加载的关卡流 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition="!bIsWorldPartition && bIsLoadLevelStreaming"), Category="Loading World")
	TArray<TSoftObjectPtr<UWorld>> LevelsToLoad;

public:
	UFUNCTION()
	void OnLoadAllLevelStreamingOnceFinish();

	UFUNCTION()
	void OnLoadAllLevelStreamingFinish();

	UFUNCTION()
	void OnLevelsToLoadOnceFinish();

	UFUNCTION()
	void OnLevelsToLoadFinish();
};
