// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"
// #include "PropertyDataSource.generated.h"

/**
 * 
 */
class PROPERTYENTITYSYSTEM_API FPropertyDataSource : public TSharedFromThis<FPropertyDataSource>
{
public:
	FPropertyDataSource(const TArray<FString>& InDynamicPath);

	virtual ~FPropertyDataSource() { return; }

	virtual void Startup(UObject* InContext, FSimpleDelegate StartupCompleteCallback) { StartupCompleteCallback.ExecuteIfBound(); }
	
	virtual bool Resolve(UObject* InContext);

	virtual FString GetValue(UObject* InContext) const;

	virtual void SetValue(UObject* InContext, const FString& Value);

	virtual FString ToString() const;

private:
	FCachedPropertyPath DynamicPath;
};
