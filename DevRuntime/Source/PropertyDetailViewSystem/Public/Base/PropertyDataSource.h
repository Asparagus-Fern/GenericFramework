// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ULocalPlayer;

class PROPERTYDETAILVIEWSYSTEM_API FPropertyDataSource : public TSharedFromThis<FPropertyDataSource>
{
public:
	virtual ~FPropertyDataSource() { return; }

	virtual void Startup(ULocalPlayer* InLocalPlayer, FSimpleDelegate StartupCompleteCallback) { StartupCompleteCallback.ExecuteIfBound(); }

	virtual bool Resolve(ULocalPlayer* InContext) = 0;

	virtual FString GetValueAsString(ULocalPlayer* InContext) const = 0;

	virtual void SetValue(ULocalPlayer* InContext, const FString& Value) = 0;

	virtual FString ToString() const = 0;
};
