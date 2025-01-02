// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureType.h"
#include "Manager/CoreInternalManager.h"
#include "ProcedureManager.generated.h"

/**
 * todo:废弃重写
 */
UCLASS()
class DEVCORE_API UProcedureManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

	/* todo:以Task方式重写？ */
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

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
