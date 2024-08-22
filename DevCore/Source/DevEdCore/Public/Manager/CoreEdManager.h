// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerEdInterface.h"
#include "Manager/CoreManager.h"
#include "CoreEdManager.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVEDCORE_API UCoreEdManager : public UCoreManager, public IManagerEdInterface
{
	GENERATED_BODY()

public:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
};
