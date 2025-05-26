// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Base/PropertyDataSource.h"

FPropertyDataSource::FPropertyDataSource(const TArray<FString>& InDynamicPath)
	: DynamicPath(InDynamicPath)
{
}

bool FPropertyDataSource::Resolve(UObject* InContext)
{
	return DynamicPath.Resolve(InContext);
}

FString FPropertyDataSource::GetValueAsString(UObject* InContext) const
{
	FString OutStringValue;

	const bool bSuccess = PropertyPathHelpers::GetPropertyValueAsString(InContext, DynamicPath, OutStringValue);
	ensure(bSuccess);

	return OutStringValue;
}

void FPropertyDataSource::SetValueByString(UObject* InContext, const FString& InStringValue)
{
	const bool bSuccess = PropertyPathHelpers::SetPropertyValueFromString(InContext, DynamicPath, InStringValue);
	ensure(bSuccess);
}

FString FPropertyDataSource::ToString() const
{
	return DynamicPath.ToString();
}
