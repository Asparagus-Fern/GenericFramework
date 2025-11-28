// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Property.generated.h"

class UPropertyDataSource;
class UPropertyProxy;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UBPFunctions_Property : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Property.Proxy"))
	static bool ExistPropertyProxy(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="Property.Proxy", DeterminesOutputType = "InPropertyProxyClass"))
	static UPropertyProxy* GetPropertyProxy(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);

public:
	UFUNCTION(BlueprintPure)
	static UPropertyDataSource* CreateDataSourceByStringPath(UObject* InContainer, const FString& InGetterPath, const FString& InSetterPath);

	UFUNCTION(BlueprintPure)
	static UPropertyDataSource* CreateDataSourceByStringArrayPath(UObject* InContainer, const TArray<FString>& InGetterPath, const TArray<FString>& InSetterPath);
};
