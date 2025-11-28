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

UPropertyProxy* UPropertySubsystem::RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyDataSourceCollection>& InPropertyProxyClass)
{
	if (InPropertyProxyTag.IsValid())
	{
		if (!InPropertyProxyTag.MatchesAny(TAG_PropertyProxy.GetTag().GetSingleTagContainer()))
		{
			GenericLOG(GenericLogProperty, Error, TEXT("PropertyProxyTag Is Not Under Property.Proxy"))
			return nullptr;
		}

		if (UPropertyProxy* PropertyProxy = GetPropertyProxy(InPropertyProxyTag))
		{
			return PropertyProxy;
		}
	}

	UPropertyProxy* NewPropertyProxy = NewObject<UPropertyProxy>(this);
	NewPropertyProxy->SetPropertyProxyTag(InPropertyProxyTag);
	NewPropertyProxy->SetPropertyDataSourceCollection(InPropertyProxyClass);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnPropertyProxyRegister, BPDelegate_OnPropertyProxyRegister, InPropertyProxyTag, NewPropertyProxy);

	if (!NewPropertyProxy->Initialize())
	{
		NewPropertyProxy->MarkAsGarbage();
		GenericLOG(GenericLogProperty, Error, TEXT("Register Property Proxy Fail!"))
		return nullptr;
	}

	PropertyProxyList.Emplace(NewPropertyProxy);
	BROADCAST_UNIFIED_DELEGATE(Delegate_PostPropertyProxyRegister, BPDelegate_PostPropertyProxyRegister, InPropertyProxyTag, NewPropertyProxy);

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

	BROADCAST_UNIFIED_DELEGATE(Delegate_PrePropertyProxyUnRegister, BPDelegate_PrePropertyProxyUnRegister, PropertyProxyTag, InPropertyProxy);
	InPropertyProxy->Deinitialize();
	PropertyProxyList.Remove(InPropertyProxy);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnPropertyProxyUnRegister, BPDelegate_OnPropertyProxyUnRegister, PropertyProxyTag, InPropertyProxy);
}

bool UPropertySubsystem::ExistPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	for (auto& PropertyProxy : PropertyProxyList)
	{
		if (InPropertyProxyTag.IsValid() && PropertyProxy->GetPropertyProxyTag() == InPropertyProxyTag)
		{
			return true;
		}
	}
	return false;
}

UPropertyProxy* UPropertySubsystem::GetPropertyProxy(FGameplayTag InPropertyProxyTag) const
{
	for (auto& PropertyProxy : PropertyProxyList)
	{
		if (InPropertyProxyTag.IsValid() && PropertyProxy->GetPropertyProxyTag() == InPropertyProxyTag)
		{
			return PropertyProxy;
		}
	}
	return nullptr;
}
