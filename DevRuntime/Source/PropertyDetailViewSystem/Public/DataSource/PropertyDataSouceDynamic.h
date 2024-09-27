// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"
#include "Base/PropertyDataSource.h"


/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyDataSouceDynamic : public FPropertyDataSource
{
public:
	FPropertyDataSouceDynamic(const TArray<FString>& InDynamicPath);

	virtual bool Resolve(ULocalPlayer* InLocalPlayer) override;

	virtual FString GetValueAsString(ULocalPlayer* InLocalPlayer) const override;

	virtual void SetValue(ULocalPlayer* InLocalPlayer, const FString& Value) override;

	virtual FString ToString() const override;

private:
	FCachedPropertyPath DynamicPath;
};
