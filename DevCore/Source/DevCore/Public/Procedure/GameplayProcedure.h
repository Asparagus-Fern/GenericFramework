// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureBaseInterface.h"
#include "ProcedureInterface.h"
#include "ProcedureObject.h"
#include "Object/CommonObject.h"
#include "UObject/Object.h"
#include "GameplayProcedure.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DEVCORE_API UGameplayProcedure : public UProcedureObject
{
	GENERATED_BODY()

public:
	virtual void MarkAsActivedFinish_Implementation() override;
	virtual void MarkAsInactivedFinish_Implementation() override;

public:
	/* 是否自动激活下个流程 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAutoActivateNextProcedure = false;

	/* 下一个流程的Tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	FGameplayTag NextProcedureTag;
};
