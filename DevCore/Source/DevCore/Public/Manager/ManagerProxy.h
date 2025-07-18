// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "ManagerType.h"
#include "Generic/GenericObject.h"
#include "Interface/WorldInterface.h"
#include "ManagerProxy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerRegister, const FManagerHandle&, ManagerHandle);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerUnRegister, const FManagerHandle&, ManagerHandle);

/**
 * 
 */
UCLASS(MinimalAPI)
class UManagerProxy final : public UGenericObject, public IWorldInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Manager")
	static DEVCORE_API UManagerProxy* GetManagerProxy();

public:
	DEVCORE_API bool ExistManager(FGuid InManagerID) const;
	DEVCORE_API bool ExistManager(const UObject* InManagerOwner) const;
	DEVCORE_API bool ExistManager(const TSubclassOf<UObject>& InManagerOwnerClass) const;
	DEVCORE_API bool GetManagerHandle(FGuid InManagerID, FManagerHandle& OutManagerHandle) const;
	DEVCORE_API bool GetManagerOwner(FGuid InManagerID, UObject*& OutManagerOwner) const;
	DEVCORE_API bool GetManager(FGuid InManagerID, TSharedRef<FCoreInternalManager>& OutManager) const;
	DEVCORE_API TArray<FManagerHandle> GetAllManagerHandles() const;

public:
	/* Is Specific Class Of Manager Object Exist */
	template <typename T>
	bool ExistManagerOwner()
	{
		for (const auto& Manager : ManagerList)
		{
			if (Manager.Value.GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return true;
			}
		}
		return false;
	}

	/* Get Specific Manager Object By Class */
	template <typename T>
	T* GetManagerOwner()
	{
		for (const auto& Manager : ManagerList)
		{
			if (Manager.Value.GetManagerOwner()->GetClass() == T::StaticClass())
			{
				return Cast<T>(Manager.Value.GetManagerOwner());
			}
		}
		return nullptr;
	}

public:
	UPROPERTY(BlueprintAssignable)
	FOnManagerRegister OnManagerRegister;

	UPROPERTY(BlueprintAssignable)
	FOnManagerUnRegister OnManagerUnRegister;

	/* ==================== IWorldInterface ==================== */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override;
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override;

	/* ==================== UManagerProxy ==================== */
public:
	DEVCORE_API bool RegisterManager(const FManagerHandle& InManagerHandle, FGuid& OutManagerID);
	DEVCORE_API bool UnRegisterManager(FGuid InManagerID);

private:
	void InitializeInternal();

	static UManagerProxy* Instance;
	bool bIsInitialize = false;

	UPROPERTY()
	TMap<FGuid, FManagerHandle> ManagerList;
};
