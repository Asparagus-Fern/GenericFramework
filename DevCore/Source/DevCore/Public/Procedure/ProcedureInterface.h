// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureBaseInterface.h"
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

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Interface")
	void OnActived();
	virtual void NativeOnActived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Interface")
	void OnInactived();
	virtual void NativeOnInactived();
};
