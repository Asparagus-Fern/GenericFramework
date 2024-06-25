// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "UObject/Interface.h"
#include "UserWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUserWidgetInterface : public UProcedureBaseInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCREENWIDGETGENERATION_API IUserWidgetInterface : public IProcedureBaseInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="User Widget Interface")
	void OnOpen();
	virtual void NativeOnOpen();

	UFUNCTION(BlueprintNativeEvent, Category="User Widget Interface")
	void OnClose();
	virtual void NativeOnClose();
};
