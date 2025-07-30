// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "HandleBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UHandleBase : public UGenericObject
{
	GENERATED_BODY()

public:
	EVENTUTILITIES_API FGuid GetHandleID() const { return HandleID; }

public:
	EVENTUTILITIES_API virtual void OnRegister() { return; }
	EVENTUTILITIES_API virtual void OnUnRegister() { return; }

public:
	UFUNCTION(BlueprintCallable)
	EVENTUTILITIES_API void UnRegister();

public:
	UFUNCTION(BlueprintCallable)
	EVENTUTILITIES_API FName GetHandleName();

	UFUNCTION(BlueprintCallable)
	EVENTUTILITIES_API void SetHandleName(FName InHandleName);

	UFUNCTION(BlueprintCallable)
	EVENTUTILITIES_API FText GetHandleDisplayName();

	UFUNCTION(BlueprintCallable)
	EVENTUTILITIES_API void SetHandleDisplayName(FText InHandleDisplayName);

public:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "==", BlueprintAutocast))
	EVENTUTILITIES_API bool EqualID(const UHandleBase* Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "==", BlueprintAutocast))
	EVENTUTILITIES_API bool EqualName(FName Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "!=", BlueprintAutocast))
	EVENTUTILITIES_API bool NotEqualID(const UHandleBase* Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "!=", BlueprintAutocast))
	EVENTUTILITIES_API bool NotEqualName(FName Other);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "Valid", BlueprintAutocast))
	EVENTUTILITIES_API bool IsHandleValid();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(CompactNodeTitle = "InValid", BlueprintAutocast))
	EVENTUTILITIES_API bool IsHandleInValid();

protected:
	FGuid HandleID;
	FName HandleName;
	FText HandleDisplayName;
};
