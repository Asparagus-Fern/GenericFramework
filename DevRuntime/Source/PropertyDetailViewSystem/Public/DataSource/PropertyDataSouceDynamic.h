// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDataSource.h"
#include "PropertyPathHelpers.h"

/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyDataSouceDynamic : public FPropertyDataSource
{
public:
	FPropertyDataSouceDynamic(const TArray<FString>& InDynamicPath);

	virtual bool Resolve(UObject* InContext) override;

	virtual FString GetValueAsString(UObject* InContext) const override;

	virtual void SetValue(UObject* InContext, const FString& Value) override;

	virtual FString ToString() const override;

private:
	FCachedPropertyPath DynamicPath;
};
