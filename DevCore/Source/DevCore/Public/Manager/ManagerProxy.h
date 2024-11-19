// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "Object/CommonObject.h"
#include "ManagerProxy.generated.h"

class FCoreInternalManager;

/**
 * 
 */
UCLASS(Transient)
class DEVCORE_API UManagerProxy : public UCommonObject
{
	GENERATED_BODY()

public:
	static UManagerProxy* InitializeManagerProxy();
	static UManagerProxy* Get();

	void RegisterManager(FCoreInternalManager* InManager);
	void UnRegisterManager(FCoreInternalManager* InManager);

	bool IsManagerExist(const FCoreInternalManager* InManager);
	bool IsManagerExist(FGuid InManagerID);

	template <typename T>
	T* GetManager()
	{
		for (const auto& Manager : ManagerMapping)
		{
			if (Manager.Value->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return Cast<T>(Manager.Value->GetManagerOwner());
			}
		}
		return nullptr;
	}

	template <typename T>
	T* GetManager(FGuid ManagerID)
	{
		for (const auto& Manager : ManagerMapping)
		{
			if (Manager.Value->GetManagerOwner()->GetClass() == T::StaticClass() && Manager.Key == ManagerID)
			{
				return Cast<T>(Manager.Value->GetManagerOwner());
			}
		}
		return nullptr;
	}

	template <typename T>
	TArray<T*> GetManagers()
	{
		TArray<T*> Result;

		for (const auto& Manager : ManagerMapping)
		{
			if (Manager.Value->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				Result.Add(Cast<T>(Manager.Value->GetManagerOwner()));
			}
		}

		return Result;
	}

protected:
	virtual void InitializeInternal();

private:
	static UManagerProxy* Instance;
	bool bIsInitialize = false;
	TMap<FGuid, FCoreInternalManager*> ManagerMapping;

	void HandleOnWorldCreation(UWorld* InWorld);
	void HandleOnWorldBeginTearDown(UWorld* InWorld);

	void HandleOnWorldBeginPlay(UWorld* InWorld);
	void HandleOnWorldMatchStarting(UWorld* InWorld);
	void HandleOnWorldEndPlay(UWorld* InWorld);
};
