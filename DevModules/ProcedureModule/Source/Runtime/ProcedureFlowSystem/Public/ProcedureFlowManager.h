// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	void RegisterFlow(UProcedureFlowComponent* InComponent);
	void UnRegisterFlow(UProcedureFlowComponent* InComponent);

private:
	UPROPERTY(Transient)
	TArray<UProcedureFlowComponent*> ProcedureFlowComponents;
};
