// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/SessionAsyncActionBase.h"

USessionAsyncActionBase::USessionAsyncActionBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetFlags(RF_StrongRefOnFrame);
}

IOnlineSessionPtr USessionAsyncActionBase::GetOnlineSessionPtr()
{
	return Online::GetSessionInterface(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull));
}
