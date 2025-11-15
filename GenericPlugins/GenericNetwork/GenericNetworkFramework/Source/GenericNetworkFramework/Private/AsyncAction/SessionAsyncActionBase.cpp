// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/SessionAsyncActionBase.h"

IOnlineSessionPtr USessionAsyncActionBase::GetOnlineSessionPtr() 
{
	return Online::GetSessionInterface(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull));
}
