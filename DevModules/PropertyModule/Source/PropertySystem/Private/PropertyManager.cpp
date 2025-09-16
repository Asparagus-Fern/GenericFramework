// Copyright ChenTaiye 2025. All Rights Reserved.


#include "PropertyManager.h"

#include "PropertyProxy.h"

bool UPropertyManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UPropertyManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UPropertyManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

UPropertyProxy* UPropertyManager::RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	if (ExistPropertyProxy(InPropertyProxyClass))
	{
		return GetPropertyProxy(InPropertyProxyClass);
	}

	UPropertyProxy* NewPropertyProxy = NewObject<UPropertyProxy>(this, InPropertyProxyClass);
	NewPropertyProxy->NativeOnCreate();
	PropertyProxies.Add(NewPropertyProxy);

	return NewPropertyProxy;
}

void UPropertyManager::UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
{
	if (ExistPropertyProxy(InPropertyProxy))
	{
		return;
	}

	InPropertyProxy->NativeOnDestroy();
	PropertyProxies.Remove(InPropertyProxy);
}

bool UPropertyManager::ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	for (auto& PropertyProxy : PropertyProxies)
	{
		if (PropertyProxy->IsA(InPropertyProxyClass))
		{
			return true;
		}
	}
	return false;
}

bool UPropertyManager::ExistPropertyProxy(const UPropertyProxy* InPropertyProxy)
{
	if (!IsValid(InPropertyProxy))
	{
		return false;
	}
	
	for (auto& PropertyProxy : PropertyProxies)
	{
		if (PropertyProxy->IsA(InPropertyProxy->GetClass()))
		{
			return true;
		}
	}
	return false;
}

UPropertyProxy* UPropertyManager::GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	for (auto& PropertyProxy : PropertyProxies)
	{
		if (PropertyProxy->IsA(InPropertyProxyClass))
		{
			return PropertyProxy;
		}
	}
	return nullptr;
}
