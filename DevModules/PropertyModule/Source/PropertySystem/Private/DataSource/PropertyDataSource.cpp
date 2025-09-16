// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "DataSource/PropertyDataSource.h"

UPropertyDataSource* UPropertyDataSource::Create(UObject* InContainer, const FString& InGetterPath, const FString& InSetterPath)
{
	ensureAlways(InContainer);

	if (IsValid(InContainer))
	{
		UPropertyDataSource* Result = NewObject<UPropertyDataSource>(InContainer);
		Result->SetPropertyGetterPath(FCachedPropertyPath(InGetterPath));
		Result->SetPropertySetterPath(FCachedPropertyPath(InSetterPath));
		return Result;
	}

	return nullptr;
}

UPropertyDataSource* UPropertyDataSource::Create(UObject* InContainer, const TArray<FString>& InGetterPath, const TArray<FString>& InSetterPath)
{
	ensureAlways(InContainer);

	if (IsValid(InContainer))
	{
		UPropertyDataSource* Result = NewObject<UPropertyDataSource>(InContainer);
		Result->SetPropertyGetterPath(FCachedPropertyPath(InGetterPath));
		Result->SetPropertySetterPath(FCachedPropertyPath(InSetterPath));
		return Result;
	}

	return nullptr;
}

UPropertyDataSource* UPropertyDataSource::Create(UObject* InContainer, const FCachedPropertyPath& InGetterPath, const FCachedPropertyPath& InSetterPath)
{
	ensureAlways(InContainer);

	if (IsValid(InContainer))
	{
		UPropertyDataSource* Result = NewObject<UPropertyDataSource>(InContainer);
		Result->SetPropertyGetterPath(FCachedPropertyPath(InGetterPath));
		Result->SetPropertySetterPath(FCachedPropertyPath(InSetterPath));
		return Result;
	}

	return nullptr;
}

UObject* UPropertyDataSource::GetContainer() const
{
	return GetOuter();
}

bool UPropertyDataSource::Resolve() const
{
	return PropertyGetterPath.Resolve(GetContainer()) && PropertySetterPath.Resolve(GetContainer());
}

FString UPropertyDataSource::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(GetContainer(), PropertyGetterPath, OutStringValue);
	return OutStringValue;
}

void UPropertyDataSource::SetValueFromString(const FString& InValue) const
{
	PropertyPathHelpers::SetPropertyValueFromString(GetContainer(), PropertySetterPath, InValue);
}

void UPropertyDataSource::SetPropertyGetterPath(const FCachedPropertyPath& InGetterPath)
{
	PropertyGetterPath = InGetterPath;
}

void UPropertyDataSource::SetPropertySetterPath(const FCachedPropertyPath& InSetterPath)
{
	PropertySetterPath = InSetterPath;
}
