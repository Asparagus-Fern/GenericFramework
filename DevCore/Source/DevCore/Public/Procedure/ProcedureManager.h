// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureType.h"
#include "Manager/CoreManager.h"
#include "ProcedureManager.generated.h"

class UProcedureHandle;
class UGameplayProcedure;

/**
 * 
 */
UCLASS()
class DEVCORE_API UProcedureManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UProcedureManager();

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;
	virtual void NativeOnBeginPlay() override;
	virtual void NativeOnEndPlay() override;

	/* UProcedureManager */
public:
	/* 默认激活的流程 */
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag DefaultProcedureTag;

	/* 所有可到达的流程 */
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	TMap<FGameplayTag, TSoftObjectPtr<UGameplayProcedure>> GameplayProcedureObjects;

public:
	/* 切换流程 */
	UFUNCTION(BlueprintCallable)
	void SwitchProcedure(FGameplayTag InProcedureTag, bool bForce = false);

	/* 从标签获取流程数据 */
	UFUNCTION(BlueprintPure)
	UGameplayProcedure* GetGameplayProcedure(FGameplayTag InProcedureTag);

	/* 获取上一个流程标签 */
	UFUNCTION(BlueprintPure)
	FGameplayTag GetLastProcedureTag() const;

	/* 获取当前流程标签 */
	UFUNCTION(BlueprintPure)
	FGameplayTag GetCurrentProcedureTag() const;

	/* 获取所有注册流程的映射 */
	UFUNCTION(BlueprintPure)
	TMap<FGameplayTag, UGameplayProcedure*>& GetGameplayProcedureMapping();

protected:
	FGameplayTag LastProcedureTag;
	FGameplayTag CurrentProcedureTag;
	TMap<FGameplayTag, UGameplayProcedure*> GameplayProcedure;

	/* Procedure Handle */
public:
	UFUNCTION(BlueprintCallable)
	void SetActorActivateState(TSubclassOf<AActor> InActorClass, bool InActive);

public:
	virtual UProcedureHandle* RegisterProcedureHandle(const TArray<FProcedureInterfaceHandle>& InHandles, FSimpleMulticastDelegate OnHandleFinish = FSimpleMulticastDelegate(), FSimpleMulticastDelegate OnHandleReset = FSimpleMulticastDelegate());
	virtual void ResetProcedureHandle(UProcedureHandle* InHandle);

protected:
	UPROPERTY()
	TArray<UProcedureHandle*> ActiveProcedureHandles;
};
