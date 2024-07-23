// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerInterface.h"
#include "ManagerType.h"
#include "Config/ConfigInterface.h"
#include "Debug/DebugType.h"
#include "Object/CommonObject.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "CoreManager.generated.h"

/**
 * 
 */
UCLASS(Abstract, Config = Manager, DefaultConfig)
class DEVCORE_API UCoreManager : public UCommonObject
                                 , public FTickableGameObject
                                 , public IConfigInterface
                                 , public IProcedureInterface
                                 , public IManagerInterface
{
	GENERATED_BODY()

	/* UObject */
public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

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

	/* IManagerInterface */
public:
	virtual void NativeOnBeginPlay() override;
	virtual void NativeOnEndPlay() override;
};
