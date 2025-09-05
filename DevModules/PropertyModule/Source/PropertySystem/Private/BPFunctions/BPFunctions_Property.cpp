// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Property.h"

#include "PropertyManager.h"
#include "Manager/ManagerStatics.h"

UPropertyProxy* UBPFunctions_Property::RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	return GetManagerOwner<UPropertyManager>()->RegisterPropertyProxy(InPropertyProxyClass);
}

void UBPFunctions_Property::UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
{
	GetManagerOwner<UPropertyManager>()->UnRegisterPropertyProxy(InPropertyProxy);
}

bool UBPFunctions_Property::ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	return GetManagerOwner<UPropertyManager>()->ExistPropertyProxy(InPropertyProxyClass);
}

UPropertyProxy* UBPFunctions_Property::GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	return GetManagerOwner<UPropertyManager>()->GetPropertyProxy(InPropertyProxyClass);
}
