// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "UObject/Object.h"
#include "ManagerProxy.generated.h"

class FCoreInternalManager;

/**
 * 
 */
UCLASS(Transient)
class DEVCORE_API UManagerProxy : public UObject
{
	GENERATED_BODY()

public:
	static UManagerProxy* InitializeManagerProxy();
	static void DeinitializeManagerProxy();

	static UManagerProxy* Get();

	void RegistManager(FCoreInternalManager* InManager);
	void UnRegistManager(FCoreInternalManager* InManager);

	bool IsManagerExist(const FCoreInternalManager* InManager);
	bool IsManagerExist(TSubclassOf<UObject> InClass);

	template <typename T>
	T* GetManager()
	{
		for (const auto& Manager : ManagerMapping)
		{
			if (Manager->GetOwner()->GetClass() == T::StaticClass())
			{
				return Cast<T>(Manager->GetOwner());
			}
		}
		return nullptr;
	}

protected:
	virtual void InitializeInternal();
	virtual void DeinitializeInternal();

private:
	static UManagerProxy* Instance;
	bool bIsInitialize = false;
	TArray<FCoreInternalManager*> ManagerMapping;
};
