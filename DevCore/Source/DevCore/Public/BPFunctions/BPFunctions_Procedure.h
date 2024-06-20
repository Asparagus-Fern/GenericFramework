// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Procedure/ProcedureType.h"
#include "BPFunctions_Procedure.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Procedure : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool SwitchProcedure(EGameplayProcedure InProcedure);
};
