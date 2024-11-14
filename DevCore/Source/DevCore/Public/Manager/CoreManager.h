// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerType.h"
#include "Debug/DebugType.h"
#include "Object/CommonObject.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "CoreManager.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class DEVCORE_API UCoreManager : public UTickableWorldSubsystem, public IProcedureInterface
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void OnWorldEndPlay(UWorld* InWorld);
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }
	virtual bool IsTickable() const override { return bTickableInEditor ? true : bTickable; }
	virtual bool IsTickableInEditor() const override { return bTickableInEditor; }
	virtual void Tick(float DeltaSeconds) override { NativeOnRefresh(); }

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UCoreManager */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTickable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTickableInEditor = false;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnWorldMatchStarting();

	UFUNCTION(BlueprintPure)
	bool IsGameManager() const;

	UFUNCTION(BlueprintPure)
	bool IsEditorManager() const;

public:
	static UWorld* GetStaticWorld() { return StaticWorld; }
	static UWorld* StaticWorld;
};
