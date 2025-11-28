// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystem/GenericGameInstanceSubsystem.h"
#include "PropertySubsystem.generated.h"

class UPropertyDataSourceCollection;
class UPropertyProxy;

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnPropertyProxyRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnPropertyProxyRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_PostPropertyProxyRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_PostPropertyProxyRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_PrePropertyProxyUnRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_PrePropertyProxyUnRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnPropertyProxyUnRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnPropertyProxyUnRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertySubsystem : public UGenericGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static PROPERTYSYSTEM_API UPropertySubsystem* Get(const UObject* WorldContextObject);

public:
	PROPERTYSYSTEM_API UPropertyProxy* RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyDataSourceCollection>& InPropertyProxyClass);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(FGameplayTag InPropertyProxyTag);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(FGameplayTag InPropertyProxyTag) const;
	PROPERTYSYSTEM_API UPropertyProxy* GetPropertyProxy(FGameplayTag InPropertyProxyTag) const;

public:
	PROPERTYSYSTEM_API inline static FDelegate_OnPropertyProxyRegister Delegate_OnPropertyProxyRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnPropertyProxyRegister BPDelegate_OnPropertyProxyRegister;

	PROPERTYSYSTEM_API inline static FDelegate_PostPropertyProxyRegister Delegate_PostPropertyProxyRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PostPropertyProxyRegister BPDelegate_PostPropertyProxyRegister;

	PROPERTYSYSTEM_API inline static FDelegate_PrePropertyProxyUnRegister Delegate_PrePropertyProxyUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PrePropertyProxyUnRegister BPDelegate_PrePropertyProxyUnRegister;
	
	PROPERTYSYSTEM_API inline static FDelegate_OnPropertyProxyUnRegister Delegate_OnPropertyProxyUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnPropertyProxyUnRegister BPDelegate_OnPropertyProxyUnRegister;

private:
	UPROPERTY()
	TArray<TObjectPtr<UPropertyProxy>> PropertyProxyList;
};
