// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerProxy.h"
// #include "ManagerStatics.generated.h"

template <typename T>
bool ExistManager()
{
	return UManagerProxy::Get()->ExistManager<T>();
}

template <typename T>
T* GetManager()
{
	return UManagerProxy::Get()->GetManager<T>();
}

template <typename T>
T* GetManager(FGuid ManagerID)
{
	return UManagerProxy::Get()->GetManager<T>(ManagerID);
}

template <typename T>
TArray<T*> GetManagers()
{
	return UManagerProxy::Get()->GetManagers<T>();
}
