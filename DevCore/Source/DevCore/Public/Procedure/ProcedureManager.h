// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureType.h"
#include "Manager/CoreManager.h"
#include "ProcedureManager.generated.h"

class UProcedureProxy;
class UGameplayProcedure;

/**
 * 
 */
UCLASS()
class DEVCORE_API UProcedureManager : public UCoreManager
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UCoreManager */
public:
	virtual void OnWorldMatchStarting_Implementation() override;

	/* UProcedureManager */
public:
	virtual void SwitchProcedure(FGameplayTag InProcedureTag, bool bForce = false);

	virtual FGameplayTag GetLastProcedureTag();
	virtual FGameplayTag GetCurrentProcedureTag();
	virtual UGameplayProcedure* GetGameplayProcedure(FGameplayTag InProcedureTag);
	virtual TMap<FGameplayTag, UGameplayProcedure*>& GetGameplayProcedures();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	FGameplayTag LastProcedureTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	FGameplayTag CurrentProcedureTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TMap<FGameplayTag, UGameplayProcedure*> GameplayProcedures;

protected:
	virtual void LoadGameplayProcedure();

	/* Procedure Handle */
public:
	virtual UProcedureProxy* RegisterProcedureHandle(TArray<UProcedureObject*> InProcedureObjects, bool InTargetActiveState, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UProcedureProxy* RegisterProcedureHandle(TArray<FProcedureHandle> InProcedureHandles, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UProcedureProxy* RegisterProcedureHandle(FProcedureHandleGroup InHandleGroup);

protected:
	virtual void OnProcedureProxyHandleBegin(UProcedureProxy* InProcedureProxy);
	virtual void OnProcedureProxyHandlePause(UProcedureProxy* InProcedureProxy);
	virtual void OnProcedureProxyHandleContinue(UProcedureProxy* InProcedureProxy);
	virtual void OnProcedureProxyHandleStop(UProcedureProxy* InProcedureProxy);
	virtual void OnProcedureProxyHandleFinish(UProcedureProxy* InProcedureProxy);

protected:
	UPROPERTY(Transient)
	TArray<UProcedureProxy*> ActivatedProcedureProxy;
};
