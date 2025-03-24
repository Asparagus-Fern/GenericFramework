// Copyright ChenTaiye 2025. All Rights Reserved.

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

public:
	virtual bool GetIsActived() const { return bIsActived; }
	virtual void SetIsActived(const bool InActived) { bIsActived = InActived; }

protected:
	bool bIsActived = false;
};
