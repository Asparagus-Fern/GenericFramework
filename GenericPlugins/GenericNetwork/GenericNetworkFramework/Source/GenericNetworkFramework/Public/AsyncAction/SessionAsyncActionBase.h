// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SessionAsyncActionBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GENERICNETWORKFRAMEWORK_API USessionAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	IOnlineSessionPtr GetOnlineSessionPtr();

protected:
	UPROPERTY()
	UObject* WorldContextObject = nullptr;
};
