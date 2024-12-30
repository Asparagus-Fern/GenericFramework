// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/ManagerSetting.h"
#include "ProcedureFlowSetting.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUREFLOWSYSTEM_API UProcedureFlowSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere, meta=(Categories="Procedure.Flow"))
	FGameplayTag DefaultFlowTag = FGameplayTag::EmptyTag;
};
