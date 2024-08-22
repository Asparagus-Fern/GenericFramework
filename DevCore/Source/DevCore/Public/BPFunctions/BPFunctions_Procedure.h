// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Procedure.generated.h"

class UGameplayProcedure;
/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Procedure : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* 切换流程 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Procedure"))
	static void SwitchProcedure(const UObject* WorldContextObject, FGameplayTag InProcedureTag, bool bForce = false);

	/* 从标签获取流程数据 */
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Procedure"))
	static UGameplayProcedure* GetGameplayProcedure(const UObject* WorldContextObject, FGameplayTag InProcedureTag);

	/* 获取上一个流程标签 */
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static FGameplayTag GetLastProcedureTag(const UObject* WorldContextObject);

	/* 获取当前流程标签 */
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static FGameplayTag GetCurrentProcedureTag(const UObject* WorldContextObject);

	/* 获取所有注册流程的映射 */
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool GetGameplayProcedures(const UObject* WorldContextObject, TMap<FGameplayTag, UGameplayProcedure*>& GameplayProcedures);
};
