// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericThread.h"
// #include "StaticFunctions_Thread.generated.h"

template <typename T = FGenericThread, typename... ArgTypes>
static TSharedPtr<T> NewGenericThread(ArgTypes&&... Args)
{
	TSharedPtr<T> Result = T::CreateThread(Forward<ArgTypes>(Args)...);
	FGenericThread::OnThreadRegisterEvent.Broadcast(Result);
	return Result;
}
