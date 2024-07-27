// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureBaseInterface.h"
#include "UObject/Interface.h"
#include "ProcedureInterface.generated.h"

DECLARE_MULTICAST_DELEGATE(FProcedureDelegate);

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
	
public:
	virtual int32 GetProcedureOrder() { return 0; }
	virtual bool GetIsAsync() { return false; }
	virtual bool GetIsActive() { return bIsActive; }
	virtual void SetIsActive(bool InActive);
	FProcedureDelegate& GetActivateFinishDelegate() { return OnActivedFinish; }
	FProcedureDelegate& GetInactivateFinishDelegate() { return OnInactivedFinish; }

protected:
	bool bIsActive = false;

	FProcedureDelegate OnActivedFinish;
	FProcedureDelegate OnInactivedFinish;

	void RequestActivateFinish() const;
	void RequestInactivateFinish() const;
};
