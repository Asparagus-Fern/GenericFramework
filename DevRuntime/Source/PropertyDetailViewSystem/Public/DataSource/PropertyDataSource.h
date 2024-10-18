// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ULocalPlayer;

/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyDataSource : public TSharedFromThis<FPropertyDataSource>
{
public:
	virtual ~FPropertyDataSource() { return; }

	virtual void Startup(UObject* InContext, FSimpleDelegate StartupCompleteCallback) { StartupCompleteCallback.ExecuteIfBound(); }

	virtual bool Resolve(UObject* InContext) = 0;

	virtual FString GetValueAsString(UObject* InContext) const = 0;

	virtual void SetValue(UObject* InContext, const FString& Value) = 0;

	virtual FString ToString() const = 0;
};
