// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivedFinish, UObject*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInactivedFinish, UObject*)

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
	virtual bool GetIsActived() const;
	virtual void SetIsActived(const bool InActived);

	FOnActivedFinish GetOnActivedFinishDelegate() { return OnActivedFinishDelegate; }
	FOnInactivedFinish GetOnInactivedFinishDelegate() { return OnInactivedFinishDelegate; }

protected:
	bool bIsActived = false;
	FOnActivedFinish OnActivedFinishDelegate;
	FOnInactivedFinish OnInactivedFinishDelegate;

	virtual void OnActiveStateChanged() { return; }
};
