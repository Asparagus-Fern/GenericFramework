// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interface/ManagerInterface.h"
#include "Manager/ManagerStatics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PropertyManager.generated.h"

class UPropertyProxy;

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnPropertyProxyRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnPropertyProxyRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnPropertyProxyUnRegister, FGameplayTag, UPropertyProxy*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnPropertyProxyUnRegister, FGameplayTag, InPropertyProxyTag, UPropertyProxy*, InPropertyProxy);

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyManager : public UGameInstanceSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	PROPERTYSYSTEM_API UPropertyProxy* RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(FGameplayTag InPropertyProxyTag);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(FGameplayTag InPropertyProxyTag) const;
	PROPERTYSYSTEM_API UPropertyProxy* GetPropertyProxy(FGameplayTag InPropertyProxyTag) const;

public:
	PROPERTYSYSTEM_API inline static FDelegate_OnPropertyProxyRegister Delegate_OnPropertyProxyRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnPropertyProxyRegister BPDelegate_OnPropertyProxyRegister;

	PROPERTYSYSTEM_API inline static FDelegate_OnPropertyProxyUnRegister Delegate_OnPropertyProxyUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnPropertyProxyUnRegister BPDelegate_OnPropertyProxyUnRegister;

private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UPropertyProxy>> PropertyProxyMapping;
};


/**
 * 
 */
class PROPERTYSYSTEM_API FPropertyHelper
{
public:
	static UPropertyProxy* RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->RegisterPropertyProxy(InPropertyProxyTag, InPropertyProxyClass);
		}
		return nullptr;
	}

	static void UnRegisterPropertyProxy(FGameplayTag InPropertyProxyTag)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			GenericWidgetManager->UnRegisterPropertyProxy(InPropertyProxyTag);
		}
	}

	static void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			GenericWidgetManager->UnRegisterPropertyProxy(InPropertyProxy);
		}
	}

	static bool ExistPropertyProxy(FGameplayTag InPropertyProxyTag)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->ExistPropertyProxy(InPropertyProxyTag);
		}
		return false;
	}

	static UPropertyProxy* GetPropertyProxy(FGameplayTag InPropertyProxyTag)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->GetPropertyProxy(InPropertyProxyTag);
		}
		return nullptr;
	}
};
