// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ManagerInterface.h"
#include "Manager/ManagerStatics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PropertyManager.generated.h"

class UPropertyProxy;

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
	PROPERTYSYSTEM_API UPropertyProxy* RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(const UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API UPropertyProxy* GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);

private:
	UPROPERTY()
	TArray<TObjectPtr<UPropertyProxy>> PropertyProxies;
};


/**
 * 
 */
class PROPERTYSYSTEM_API FPropertyHelper
{
public:
	static UPropertyProxy* RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->RegisterPropertyProxy(InPropertyProxyClass);
		}
		return nullptr;
	}

	static void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			GenericWidgetManager->UnRegisterPropertyProxy(InPropertyProxy);
		}
	}

	static bool ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->ExistPropertyProxy(InPropertyProxyClass);
		}
		return false;
	}

	static bool ExistPropertyProxy(const UPropertyProxy* InPropertyProxy)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->ExistPropertyProxy(InPropertyProxy);
		}
		return false;
	}

	static UPropertyProxy* GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
	{
		if (UPropertyManager* GenericWidgetManager = GetManagerOwner<UPropertyManager>())
		{
			return GenericWidgetManager->GetPropertyProxy(InPropertyProxyClass);
		}
		return nullptr;
	}
};
