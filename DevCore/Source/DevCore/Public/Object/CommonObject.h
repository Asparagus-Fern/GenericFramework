// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerGlobal.h"
#include "UObject/Object.h"
#include "CommonObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEVCORE_API UCommonObject : public UObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;
};
