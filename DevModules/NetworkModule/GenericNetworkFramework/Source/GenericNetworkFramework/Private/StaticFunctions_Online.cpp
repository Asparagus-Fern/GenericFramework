// Copyright ChenTaiye 2025. All Rights Reserved.

#include "StaticFunctions_Online.h"

#include "OnlineSubsystem.h"
#include "Type/DebugType.h"

IOnlineSubsystem* FStaticFunctions_Online::GetOnlineSubsystem()
{
	return IOnlineSubsystem::GetByPlatform();
}

IOnlineSessionPtr FStaticFunctions_Online::GetOnlineSession()
{
	if (IOnlineSubsystem* OnlineSubsystem = GetOnlineSubsystem())
	{
		return OnlineSubsystem->GetSessionInterface();
	}
	else
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("OnlineSubsystem Is InValid"))
		return nullptr;
	}
}
