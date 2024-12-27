// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerInterface.h"
#include "UObject/Object.h"
#include "ManagerInfo.generated.h"

class UManagerProxy;

/**
 * 
 */
UCLASS(Transient)
class DEVCORE_API UManagerInfo : public UObject, public IManagerInterface
{
	GENERATED_BODY()

	friend UManagerProxy;

public:
	bool InitializeManagerInfo(IManagerInterface* InInterface);

	/* IManagerInterface */
public:
	virtual FGuid GetManagerID() const override { return ManagerInterface->GetManagerID(); }
	
	UFUNCTION(BlueprintPure)
	virtual UObject* GetManagerOwner() const override { return ManagerInterface->GetManagerOwner(); }

	UFUNCTION(BlueprintPure)
	virtual int32 GetManagerOrder() override { return ManagerInterface->GetManagerOrder(); }

	virtual UManagerInfo* GetManagerInfo() override { return this; }

private:
	IManagerInterface* ManagerInterface = nullptr;
};
