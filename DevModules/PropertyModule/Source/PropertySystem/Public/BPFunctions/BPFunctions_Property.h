// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Property.generated.h"

class UPropertyProxy;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UBPFunctions_Property : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "InPropertyProxyClass"))
	static UPropertyProxy* RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy);

	UFUNCTION(BlueprintPure)
	static bool ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);

	UFUNCTION(BlueprintPure, meta=(DeterminesOutputType = "InPropertyProxyClass"))
	static UPropertyProxy* GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
};
