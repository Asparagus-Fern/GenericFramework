// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "UObject/ObjectMacros.h"
#include "PropertyDataSourceInterface.h"
#include "PropertyPathHelpers.h"

/**
 * 
 */
class PROPERTYPATHSYSTEM_API FPropertyDataSource : public TSharedFromThis<FPropertyDataSource>, public IPropertyDataSourceInterface
{
public:
	FPropertyDataSource(const TArray<FString>& InDynamicPath);

	virtual bool Resolve(UObject* InContext) override;

	virtual FString GetValueAsString(UObject* InContext) const override;

	virtual void SetValueByString(UObject* InContext, const FString& Value) override;

	virtual FString ToString() const override;

private:
	FCachedPropertyPath DynamicPath;
};
