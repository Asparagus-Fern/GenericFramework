// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivedFinish, UObject*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInactivedFinish, UObject*)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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
	void HandleOnCreate();
	virtual void NativeOnCreate();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnActived();
	virtual void NativeOnActived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnActivedFinish();
	virtual void NativeOnActivedFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnRefresh();
	virtual void NativeOnRefresh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnInactived();
	virtual void NativeOnInactived();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnInactivedFinish();
	virtual void NativeOnInactivedFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="State Interface")
	void HandleOnDestroy();
	virtual void NativeOnDestroy();
	
	virtual bool GetIsActived() const;
	virtual void SetIsActived(const bool InActived);

	FOnActivedFinish& GetOnActivedFinishEvent() { return OnActivedFinishEvent; }
	FOnInactivedFinish& GetOnInactivedFinishEvent() { return OnInactivedFinishEvent; }

protected:
	virtual void OnActiveStateChanged();
	
	bool bIsActived = false;
	FOnActivedFinish OnActivedFinishEvent;
	FOnInactivedFinish OnInactivedFinishEvent;
};
