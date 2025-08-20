// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
// #include "StaticFunctions_Online.generated.h"

class IOnlineSubsystem;

class FStaticFunctions_Online
{
public:
	GENERICNETWORKFRAMEWORK_API static IOnlineSubsystem* GetOnlineSubsystem();
	GENERICNETWORKFRAMEWORK_API static IOnlineSessionPtr GetOnlineSession();
};
