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

UPropertyProxy* UPropertyManager::RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	if (!InPropertyProxyTag.IsValid())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyProxyTag Is InValid"))
		return nullptr;
	}

	if (!InPropertyProxyTag.MatchesAny(TAG_PropertyProxy.GetTag().GetSingleTagContainer()))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyProxyTag Is Not Under Property.Proxy"))
		return nullptr;
	}

	if (ExistPropertyProxy(InPropertyProxyTag))
	{
		return GetPropertyProxy(InPropertyProxyTag);
	}

	UPropertyProxy* NewPropertyProxy = NewObject<UPropertyProxy>(this, InPropertyProxyClass);
	NewPropertyProxy->SetPropertyProxyTag(InPropertyProxyTag);
	NewPropertyProxy->NativeOnCreate();

	PropertyProxyMapping.Emplace(InPropertyProxyTag, NewPropertyProxy);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnPropertyProxyRegister, BPDelegate_OnPropertyProxyRegister, InPropertyProxyTag, NewPropertyProxy);

	return NewPropertyProxy;
}

void UPropertyManager::UnRegisterPropertyProxy(FGameplayTag InPropertyProxyTag)
{
	UnRegisterPropertyProxy(GetPropertyProxy(InPropertyProxyTag));
}

void UPropertyManager::UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
{
	if (!IsValid(InPropertyProxy))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyProxy Is InValid"))
		return;
	}

	FGameplayTag PropertyProxyTag = InPropertyProxy->GetPropertyProxyTag();
	if (!ExistPropertyProxy(PropertyProxyTag))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyProxy Is Already UnRegistered"))
		return;
	}

	InPropertyProxy->NativeOnDestroy();
	PropertyProxyMapping.Remove(PropertyProxyTag);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnPropertyProxyUnRegister, BPDelegate_OnPropertyProxyUnRegister, PropertyProxyTag, InPropertyProxy);
}

bool UPropertyManager::ExistPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	return PropertyProxyMapping.Contains(InPropertyProxyTag);
}

UPropertyProxy* UPropertyManager::GetPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	if (PropertyProxyMapping.Contains(InPropertyProxyTag))
	{
		return PropertyProxyMapping.FindRef(InPropertyProxyTag);
	}
	return nullptr;
}
