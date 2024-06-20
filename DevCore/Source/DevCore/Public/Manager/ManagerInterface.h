// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManagerInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool IsEditorManager() { return false; }

	virtual bool IsSupportWorldType(const UWorld* InWorld);
	virtual EWorldType::Type GetWorldType() { return EWorldType::None; }
	virtual bool IsWorldType(EWorldType::Type InWorldType);
};
