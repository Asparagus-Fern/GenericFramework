// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IStateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnCreate();
	virtual void NativeOnCreate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnActived();
	virtual void NativeOnActived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnActivedFinish();
	virtual void NativeOnActivedFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnRefresh();
	virtual void NativeOnRefresh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnInactived();
	virtual void NativeOnInactived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnInactivedFinish();
	virtual void NativeOnInactivedFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void OnDestroy();
	virtual void NativeOnDestroy();

public:
	virtual bool GetIsActived() const { return bIsActived; }
	virtual void SetIsActived(const bool InActived) { bIsActived = InActived; }

	bool GetGarbageAtDestroy() const { return bGarbageAtDestroy; }
	void SetGarbageAtDestroy(const bool InGarbageAtDestroy) { bGarbageAtDestroy = InGarbageAtDestroy; }

protected:
	bool bIsActived = false;
	bool bGarbageAtDestroy = false;
};
