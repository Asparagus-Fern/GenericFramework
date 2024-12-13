// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "Interface/WorldInterface.h"
#include "Object/CommonObject.h"
#include "ManagerProxy.generated.h"

/**
 * 
 */
UCLASS(Transient)
class DEVCORE_API UManagerProxy : public UCommonObject, public FWorldInterface
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
	bool ExistManager()
	{
		for (const auto& Manager : ManagerMapping)
		{
			if (!Manager.Value)
			{
				continue;
			}

			if (Manager.Value->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return IsManagerExist(Manager.Value);
			}
		}
		return false;
	}

	template <typename T>
	T* GetManager()
	{
		for (const auto& Manager : ManagerMapping)
		{
			if (!Manager.Value)
			{
				continue;
			}

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

	/* FWorldInterface */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override;

	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

private:
	static UManagerProxy* Instance;
	bool bIsInitialize = false;
	TMap<FGuid, FCoreInternalManager*> ManagerMapping;
};
