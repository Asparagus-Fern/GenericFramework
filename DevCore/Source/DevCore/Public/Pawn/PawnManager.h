// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "PawnManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UPawnManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UPawnManager();

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;

	/* UPawnManager */
public:
};
