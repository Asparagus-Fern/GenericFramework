// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "DebugManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UDebugManager : public UCoreManager
{
	GENERATED_BODY()

	/* UDebugManager */
public:
	UDebugManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
