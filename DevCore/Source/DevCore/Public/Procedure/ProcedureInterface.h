// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureBaseInterface.h"
#include "ProcedureType.h"
#include "UObject/Interface.h"
#include "ProcedureInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UProcedureInterface : public UProcedureBaseInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IProcedureInterface : public IProcedureBaseInterface
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	UFUNCTION(BlueprintNativeEvent, Category="Procedure Interface")
	void OnActived();
	virtual void NativeOnActived();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Interface")
	void OnInactived();
	virtual void NativeOnInactived();

public:
	virtual int32 GetProcedureOrder() { return 0; }
	virtual bool GetIsActive() { return bIsActive; }

protected:
	bool bIsActive = false;
};
