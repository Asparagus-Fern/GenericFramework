// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProcedureFlowManager.generated.h"

class UProcedureFlowComponent;

/**
 * 
 */
UCLASS()
class PROCEDUREFLOWSYSTEM_API UProcedureFlowManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* IManagerInterface */
protected:
	virtual int32 GetManagerOrder() override { return 1; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;

	/* UProcedureFlowManager */
public:
	void RegisterFlow(UProcedureFlowComponent* InComponent);
	void UnRegisterFlow(UProcedureFlowComponent* InComponent);
	void EnterProcedureFlow(FGameplayTag InFlowTag);
	UProcedureFlowComponent* GetProcedureFlowComponent(FGameplayTag InFlowTag);

private:
	void SortProcedureFlowComponentsAsEnter();
	void SortProcedureFlowComponentsAsExit();
	void Execute(const TFunctionRef<void(UProcedureFlowComponent* InComponent)>& Func);
	
private:
	UPROPERTY(Transient)
	FGameplayTag CurrentFlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProcedureFlowComponent>> ProcedureFlowComponents;
};
