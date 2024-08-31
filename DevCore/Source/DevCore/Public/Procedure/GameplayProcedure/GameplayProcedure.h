// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Procedure/ProcedureObject.h"
#include "UObject/Object.h"
#include "GameplayProcedure.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVCORE_API UGameplayProcedure : public UProcedureObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Procedure"))
	FGameplayTag ProcedureTag;
};
