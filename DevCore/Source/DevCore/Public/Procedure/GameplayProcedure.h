// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureBaseInterface.h"
#include "ProcedureInterface.h"
#include "UObject/Object.h"
#include "GameplayProcedure.generated.h"

class UTimelineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameplayProcedureDelegate);

/**
 * 
 */
UCLASS(BlueprintType)
class DEVCORE_API UGameplayProcedure : public UObject, public IProcedureBaseInterface, public IProcedureInterface
{
	GENERATED_BODY()

public:
	UGameplayProcedure();
	virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 是否自动激活下个流程 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAutoActivateNextProcedure = false;

	/* 下一个流程的Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	FGameplayTag NextProcedureTag;

public:
	UPROPERTY(BlueprintAssignable)
	FGameplayProcedureDelegate PreProcedureActived;

	UPROPERTY(BlueprintAssignable)
	FGameplayProcedureDelegate PostProcedureActived;

	UPROPERTY(BlueprintAssignable)
	FGameplayProcedureDelegate PreProcedureInactived;

	UPROPERTY(BlueprintAssignable)
	FGameplayProcedureDelegate PostProcedureInactived;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestProcedureActived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestProcedureInactived();
};
