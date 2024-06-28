// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual int32 GetProcedureOrder() override { return -99; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UProcedureManager */
public:
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag DefaultProcedureTag;

	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	TMap<FGameplayTag, TSoftObjectPtr<UGameplayProcedure>> GameplayProcedureObjects;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchProcedure(FGameplayTag InProcedureTag, bool bForce = false);

	UFUNCTION(BlueprintCallable)
	UGameplayProcedure* GetGameplayProcedure(FGameplayTag InProcedureTag);

protected:
	FGameplayTag LastProcedureTag;
	FGameplayTag CurrentProcedureTag;
	TMap<FGameplayTag, UGameplayProcedure*> GameplayProcedure;
};
