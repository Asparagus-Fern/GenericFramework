// Fill out your copyright notice in the Description page of Project Settings.


#include "DataSource/PropertyDataSouceDynamic.h"

FPropertyDataSouceDynamic::FPropertyDataSouceDynamic(const TArray<FString>& InDynamicPath)
	: DynamicPath(InDynamicPath)
{
}

bool FPropertyDataSouceDynamic::Resolve(UObject* InContext)
{
	return DynamicPath.Resolve(InContext);
}

FString FPropertyDataSouceDynamic::GetValueAsString(UObject* InContext) const
{
	FString OutStringValue;

	const bool bSuccess = PropertyPathHelpers::GetPropertyValueAsString(InContext, DynamicPath, OutStringValue);
	ensure(bSuccess);

	return OutStringValue;
}

void FPropertyDataSouceDynamic::SetValue(UObject* InContext, const FString& InStringValue)
{
	const bool bSuccess = PropertyPathHelpers::SetPropertyValueFromString(InContext, DynamicPath, InStringValue);
	ensure(bSuccess);
}

FString FPropertyDataSouceDynamic::ToString() const
{
	return DynamicPath.ToString();
}