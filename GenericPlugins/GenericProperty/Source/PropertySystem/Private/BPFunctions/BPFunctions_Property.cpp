// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Property.h"

#include "PropertyManager.h"
#include "DataSource/PropertyDataSource.h"
#include "Manager/ManagerStatics.h"

UPropertyProxy* UBPFunctions_Property::RegisterPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	return FPropertyHelper::RegisterPropertyProxy(InPropertyProxyTag, InPropertyProxyClass);
}

void UBPFunctions_Property::UnRegisterPropertyProxyByTag(FGameplayTag InPropertyProxyTag)
{
	FPropertyHelper::UnRegisterPropertyProxy(InPropertyProxyTag);
}

void UBPFunctions_Property::UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy)
{
	FPropertyHelper::UnRegisterPropertyProxy(InPropertyProxy);
}

bool UBPFunctions_Property::ExistPropertyProxy(FGameplayTag InPropertyProxyTag)
{
	return FPropertyHelper::ExistPropertyProxy(InPropertyProxyTag);;
}

UPropertyProxy* UBPFunctions_Property::GetPropertyProxy(FGameplayTag InPropertyProxyTag, const TSubclassOf<UPropertyProxy>& InPropertyProxyClass)
{
	return FPropertyHelper::GetPropertyProxy(InPropertyProxyTag);
}

UPropertyDataSource* UBPFunctions_Property::CreateDataSourceByStringPath(UObject* InContainer, const FString& InGetterPath, const FString& InSetterPath)
{
	return UPropertyDataSource::Create(InContainer, InGetterPath, InSetterPath);
}

UPropertyDataSource* UBPFunctions_Property::CreateDataSourceByStringArrayPath(UObject* InContainer, const TArray<FString>& InGetterPath, const TArray<FString>& InSetterPath)
{
	return UPropertyDataSource::Create(InContainer, InGetterPath, InSetterPath);
}
