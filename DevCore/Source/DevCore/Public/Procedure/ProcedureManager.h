// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureType.h"
#include "Manager/CoreManager.h"
#include "ProcedureManager.generated.h"

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

protected:
	TArray<FManagerOrder> ManagerOrders;
	void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues InitializationValues);
	void OnWorldMatchStarting(UWorld* InWorld);
	void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);
	void RefreshManagerOrders();
	void ProcessManagerOrders(bool IsForwardSort, const TFunctionRef<void(UCoreManager* InCoreManager)>& Exec);

#if WITH_EDITOR

protected:
	void OnEditorClose();

#endif

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UProcedureManager */
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	EGameplayProcedure DefaultGameplayProcedure = EGameplayProcedure::GameLoading;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TMap<EGameplayProcedure, TSoftClassPtr<UGameplayProcedure>> GameplayProcedureClass;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, AdvancedDisplay)
	UWorld* EditorWorld;
#endif

public:
	UFUNCTION(BlueprintCallable)
	bool SwitchProcedure(EGameplayProcedure InProcedure, bool bForce = false);

	UFUNCTION(BlueprintCallable)
	UGameplayProcedure* GetGameplayProcedure(EGameplayProcedure InProcedure);

protected:
	EGameplayProcedure LastGameplayProcedure;
	EGameplayProcedure CurrentGameplayProcedure;
	TMap<EGameplayProcedure, UGameplayProcedure*> GameplayProcedure;
};
