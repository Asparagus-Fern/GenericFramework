// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerInterface.h"
#include "ManagerType.h"
#include "Config/ConfigInterface.h"
#include "Debug/DebugType.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManagerInterface.h"
#include "CoreManager.generated.h"

/**
 * 
 */
UCLASS(Abstract, Config = Manager, DefaultConfig)
class DEVCORE_API UCoreManager : public UObject, public FTickableGameObject, public IConfigInterface, public IProcedureManagerInterface, public IManagerInterface
{
	GENERATED_BODY()

public:
	UCoreManager();

	/* UObject */
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual UWorld* GetWorld() const override;

	/* UCoreManager */
public:
	UPROPERTY(Transient, VisibleAnywhere)
	UWorld* ManagerWorld;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = -99, ClampMax = 99))
	int32 ProcedureOrder = 0;

	/* FTickableGameObject */
public:
	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }
	virtual bool IsTickable() const override { return false; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual void Tick(float DeltaSeconds) override { return; }
	
	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IProcedureManagerInterface */
public:
	virtual void NativePreProcedureSwitch(EGameplayProcedure InOldProcedure, EGameplayProcedure InNewProcedure) override;
	virtual void NativePostProcedureSwitch(EGameplayProcedure InProcedure) override;
};
