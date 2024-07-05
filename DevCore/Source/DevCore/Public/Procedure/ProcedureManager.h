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
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag DefaultProcedureTag;

	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	TMap<FGameplayTag, TSoftObjectPtr<UGameplayProcedure>> GameplayProcedureObjects;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchProcedure(FGameplayTag InProcedureTag, bool bForce = false);

	UFUNCTION(BlueprintCallable)
	UGameplayProcedure* GetGameplayProcedure(FGameplayTag InProcedureTag);

protected:
	FGameplayTag LastProcedureTag;
	FGameplayTag CurrentProcedureTag;
	TMap<FGameplayTag, UGameplayProcedure*> GameplayProcedure;

	/* Procedure Handle */
public:
	virtual UProcedureHandle* RegisterProcedureHandle(const TArray<FProcedureInterfaceHandle>& InHandles, FSimpleMulticastDelegate OnHandleFinish = FSimpleMulticastDelegate(), FSimpleMulticastDelegate OnHandleReset = FSimpleMulticastDelegate());
	virtual void ResetProcedureHandle(UProcedureHandle* InHandle);

protected:
	UPROPERTY()
	TArray<UProcedureHandle*> ActiveProcedureHandles;
};
