// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ManagerProxy.h"
// #include "ManagerStatics.generated.h"

template <typename T>
T* GetManagerOwner()
{
	return UManagerProxy::GetManagerProxy()->GetManagerOwner<T>();
}