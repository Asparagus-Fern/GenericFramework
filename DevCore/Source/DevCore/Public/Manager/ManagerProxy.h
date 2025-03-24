// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "ManagerInfo.h"
#include "Common/CommonObject.h"
#include "Interface/WorldInterface.h"
#include "ManagerProxy.generated.h"

class UManagerInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerRegister, UManagerInfo*, ManagerInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerUnRegister, UManagerInfo*, ManagerInfo);

/**
 * 
 */
UCLASS()
class DEVCORE_API UManagerProxy : public UCommonObject, public IWorldInterface
{
	GENERATED_BODY()

public:
	static UManagerProxy* InitializeManagerProxy();
	static void DeInitializeManagerProxy();
	static UManagerProxy* Get();

	void RegisterManager(IManagerInterface* InManager);
	void UnRegisterManager(const IManagerInterface* InManager);

	bool IsManagerExist(const IManagerInterface* InManager);
	bool IsManagerExist(FGuid InManagerID);

	/* Is Specific Class Of Manager Object Exist */
	template <typename T>
	bool ExistManager()
	{
		for (const auto& Manager : ManagerInfos)
		{
			if (Manager->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return IsManagerExist(Manager);
			}
		}
		return false;
	}

	/* Is Specific Class Of Manager Object Exist */
	template <typename T>
	bool ExistManager(FGuid ManagerID)
	{
		for (const auto& Manager : ManagerInfos)
		{
			if (Manager->GetManagerOwner()->GetClass() == T::StaticClass() && Manager->GetManagerID() == ManagerID)
			{
				return IsManagerExist(Manager);
			}
		}
		return false;
	}

	/* Get Specific Manager Object By Class */
	template <typename T>
	T* GetManager()
	{
		for (const auto& Manager : ManagerInfos)
		{
			if (Manager->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return Cast<T>(Manager->GetManagerOwner());
			}
		}
		return nullptr;
	}

	/* Get Specific Manager Object By Guid */
	template <typename T>
	T* GetManager(FGuid ManagerID)
	{
		for (const auto& Manager : ManagerInfos)
		{
			if (Manager->GetManagerOwner()->GetClass() == T::StaticClass() && Manager->GetManagerID() == ManagerID)
			{
				return Cast<T>(Manager->GetManagerOwner());
			}
		}
		return nullptr;
	}

	/* Get Specific Manager Objects */
	template <typename T>
	TArray<T*> GetManagers()
	{
		TArray<T*> Result;

		for (const auto& Manager : ManagerInfos)
		{
			if (Manager->GetManagerOwner()->GetClass() == T::StaticClass())
			{
				Result.Add(Cast<T>(Manager->GetManagerOwner()));
			}
		}

		return Result;
	}

	/* Sort ManagerInfos With ManagerOrder */
	void SortManagers();

	/* Get Specific ManagerInfo By Interface */
	UManagerInfo* GetManagerInfo(const IManagerInterface* InManager) const;

	/* Get Specific ManagerInfo By Guid */
	UManagerInfo* GetManagerInfo(FGuid ManagerID) const;

	/* Get Specific ManagerInfo By ManagerName */
	UManagerInfo* GetManagerInfo(FName ManagerName) const;

	/* Get All ManagerInfos */
	TArray<UManagerInfo*> GetManagerInfos();

public:
	UPROPERTY(BlueprintAssignable)
	FOnManagerRegister OnManagerRegister;

	UPROPERTY(BlueprintAssignable)
	FOnManagerUnRegister OnManagerUnRegister;

protected:
	virtual void InitializeInternal();

	/* IWorldInterface */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override;

	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

private:
	static UManagerProxy* Instance;
	bool bIsInitialize = false;

	UPROPERTY()
	TArray<UManagerInfo*> ManagerInfos;
};
