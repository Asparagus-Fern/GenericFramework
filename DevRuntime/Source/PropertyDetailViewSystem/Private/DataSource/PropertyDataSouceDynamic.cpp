// Fill out your copyright notice in the Description page of Project Settings.


#include "DataSource/PropertyDataSouceDynamic.h"

FPropertyDataSouceDynamic::FPropertyDataSouceDynamic(const TArray<FString>& InDynamicPath)
	: DynamicPath(InDynamicPath)
{
}

bool FPropertyDataSouceDynamic::Resolve(ULocalPlayer* InLocalPlayer)
{
	return DynamicPath.Resolve(InLocalPlayer);
}

FString FPropertyDataSouceDynamic::GetValueAsString(ULocalPlayer* InLocalPlayer) const
{
	FString OutStringValue;

	const bool bSuccess = PropertyPathHelpers::GetPropertyValueAsString(InLocalPlayer, DynamicPath, OutStringValue);
	ensure(bSuccess);

	return OutStringValue;
}

void FPropertyDataSouceDynamic::SetValue(ULocalPlayer* InLocalPlayer, const FString& InStringValue)
{
	const bool bSuccess = PropertyPathHelpers::SetPropertyValueFromString(InLocalPlayer, DynamicPath, InStringValue);
	ensure(bSuccess);
}

FString FPropertyDataSouceDynamic::ToString() const
{
	return DynamicPath.ToString();
}