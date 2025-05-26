// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "PropertyDataSourceInterface.generated.h"

/**
 * 
 */
class IPropertyDataSourceInterface
{
public:
	virtual ~IPropertyDataSourceInterface() = default;

	virtual void Startup(UObject* InContext, FSimpleDelegate StartupCompleteCallback) { StartupCompleteCallback.ExecuteIfBound(); }

	virtual bool Resolve(UObject* InContext) = 0;

	virtual FString GetValueAsString(UObject* InContext) const = 0;

	virtual void SetValueByString(UObject* InContext, const FString& Value) = 0;

	virtual FString ToString() const = 0;
};
