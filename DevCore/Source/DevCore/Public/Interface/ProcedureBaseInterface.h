// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProcedureBaseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProcedureBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IProcedureBaseInterface
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Base Interface")
	void OnCreate();
	virtual void NativeOnCreate();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Base Interface")
	void OnRefresh();
	virtual void NativeOnRefresh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Base Interface")
	void OnDestroy();
	virtual void NativeOnDestroy();
};
