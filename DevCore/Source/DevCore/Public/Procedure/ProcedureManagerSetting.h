// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/ManagerSetting.h"
#include "ProcedureManagerSetting.generated.h"

class UGameplayProcedure;

/**
 * 
 */
UCLASS()
class DEVCORE_API UProcedureManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	/* 默认激活的流程 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag DefaultProcedureTag;

	/* 所有可到达的流程 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	TMap<FGameplayTag, TSoftObjectPtr<UGameplayProcedure>> GameplayProcedures;
};
