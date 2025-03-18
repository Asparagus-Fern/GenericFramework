// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PropertyDataSource.h"

FPropertyDataSource::FPropertyDataSource(const TArray<FString>& InDynamicPath)
	: DynamicPath(InDynamicPath)
{
}

bool FPropertyDataSource::Resolve(UObject* InContext)
{
	return DynamicPath.Resolve(InContext);
}

FString FPropertyDataSource::GetValue(UObject* InContext) const
{
	FString OutStringValue;

	const bool bSuccess = PropertyPathHelpers::GetPropertyValueAsString(InContext, DynamicPath, OutStringValue);
	ensure(bSuccess);

	return OutStringValue;
}

void FPropertyDataSource::SetValue(UObject* InContext, const FString& Value)
{
}

FString FPropertyDataSource::ToString() const
{
	return DynamicPath.ToString();
}
