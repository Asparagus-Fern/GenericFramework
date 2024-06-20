// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerInterface.h"
#include "ManagerType.h"
#include "Debug/DebugType.h"
#include "Procedure/ProcedureManagerInterface.h"
#include "StaticFunctions/StaticFunctions_Manager.h"
#include "CoreManager.generated.h"

/**
 * 
 */
UCLASS(Abstract, Config = Manager, DefaultConfig)
class DEVCORE_API UCoreManager : public UEngineSubsystem, public FTickableGameObject, public IProcedureManagerInterface, public IManagerInterface
{
	GENERATED_BODY()

public:
	UCoreManager();
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

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

	/* Ini Save */
protected:
	FString GetSaveIniPath() { return GetSaveIniBasePath() + GetSaveIniRelativePath() + GetSaveIniFileName(); }
	virtual FString GetSaveIniBasePath() { return FPaths::ProjectConfigDir(); }
	virtual FString GetSaveIniRelativePath() { return ""; }
	virtual FString GetSaveIniFileName() { return "DefaultManager.ini"; }

	/* IManagerInterface */
protected:
	virtual EWorldType::Type GetWorldType() override { return GetWorld()->WorldType; }

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;

	/* IProcedureManagerInterface */
public:
	virtual void NativePreProcedureSwitch(EGameplayProcedure InOldProcedure, EGameplayProcedure InNewProcedure) override;
	virtual void NativePostProcedureSwitch(EGameplayProcedure InProcedure) override;
};
