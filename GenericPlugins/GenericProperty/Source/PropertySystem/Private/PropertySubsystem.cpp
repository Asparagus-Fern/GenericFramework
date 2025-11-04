// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertySubsystem.h"

#include "PropertyProxy.h"
#include "Type/GenericType.h"

UPropertySubsystem* UPropertySubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance()->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

UPropertyProxy* UPropertySubsystem::RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
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

void UPropertySubsystem::UnRegisterPropertyProxy(FGameplayTag InPropertyProxyTag)
{
	UnRegisterPropertyProxy(GetPropertyProxy(InPropertyProxyTag));
}

void UPropertySubsystem::UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
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

bool UPropertySubsystem::ExistPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	return PropertyProxyMapping.Contains(InPropertyProxyTag);
}

UPropertyProxy* UPropertySubsystem::GetPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	if (PropertyProxyMapping.Contains(InPropertyProxyTag))
	{
		return PropertyProxyMapping.FindRef(InPropertyProxyTag);
	}
	return nullptr;
}
