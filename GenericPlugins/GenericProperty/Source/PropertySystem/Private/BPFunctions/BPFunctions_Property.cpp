// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Property.h"

#include "PropertySubsystem.h"
#include "DataSource/PropertyDataSource.h"

UPropertyProxy* UBPFunctions_Property::RegisterPropertyProxy(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(WorldContextObject))
	{
		return PropertySubsystem->RegisterPropertyProxy(InPropertyProxyTag, InPropertyProxyClass);
	}
	return nullptr;
}

void UBPFunctions_Property::UnRegisterPropertyProxyByTag(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag)
{
	if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(WorldContextObject))
	{
		return PropertySubsystem->UnRegisterPropertyProxy(InPropertyProxyTag);
	}
}

void UBPFunctions_Property::UnRegisterPropertyProxy(const UObject* WorldContextObject, UPropertyProxy* InPropertyProxy)
{
	if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(WorldContextObject))
	{
		return PropertySubsystem->UnRegisterPropertyProxy(InPropertyProxy);
	}
}

bool UBPFunctions_Property::ExistPropertyProxy(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag)
{
	if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(WorldContextObject))
	{
		return PropertySubsystem->ExistPropertyProxy(InPropertyProxyTag);
	}
	return false;
}

UPropertyProxy* UBPFunctions_Property::GetPropertyProxy(const UObject* WorldContextObject, FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	if (UPropertySubsystem* GenericWidgetSubsystem = UPropertySubsystem::Get(WorldContextObject))
	{
		return GenericWidgetSubsystem->GetPropertyProxy(InPropertyProxyTag);
	}
	return nullptr;
}

UPropertyDataSource* UBPFunctions_Property::CreateDataSourceByStringPath(UObject* InContainer, const FString& InGetterPath, const FString& InSetterPath)
{
	return UPropertyDataSource::Create(InContainer, InGetterPath, InSetterPath);
}

UPropertyDataSource* UBPFunctions_Property::CreateDataSourceByStringArrayPath(UObject* InContainer, const TArray<FString>& InGetterPath, const TArray<FString>& InSetterPath)
{
	return UPropertyDataSource::Create(InContainer, InGetterPath, InSetterPath);
}
