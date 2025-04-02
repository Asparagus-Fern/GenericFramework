// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "HandleBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class EVENTUTILITIES_API UHandleBase : public UGenericObject
{
	GENERATED_BODY()

public:
	FGuid GetHandleID() const { return HandleID; }

public:
	virtual void OnRegister() { return; }
	virtual void OnUnRegister() { return; }

public:
	UFUNCTION(BlueprintCallable)
	void UnRegister();

public:
	UFUNCTION(BlueprintCallable)
	FName GetHandleName();

	UFUNCTION(BlueprintCallable)
	void SetHandleName(FName InHandleName);

	UFUNCTION(BlueprintCallable)
	FText GetHandleDisplayName();

	UFUNCTION(BlueprintCallable)
	void SetHandleDisplayName(FText InHandleDisplayName);

public:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "==", BlueprintAutocast))
	bool EqualID(const UHandleBase* Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "==", BlueprintAutocast))
	bool EqualName(FName Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "!=", BlueprintAutocast))
	bool NotEqualID(const UHandleBase* Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "!=", BlueprintAutocast))
	bool NotEqualName(FName Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "Valid", BlueprintAutocast))
	bool IsHandleValid();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "InValid", BlueprintAutocast))
	bool IsHandleInValid();

protected:
	FGuid HandleID;
	FName HandleName;
	FText HandleDisplayName;
};
