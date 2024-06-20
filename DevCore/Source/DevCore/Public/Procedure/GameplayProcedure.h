// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureInterface.h"
#include "UObject/Object.h"
#include "GameplayProcedure.generated.h"


/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class DEVCORE_API UGameplayProcedure : public UObject, public IProcedureInterface
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;
};
