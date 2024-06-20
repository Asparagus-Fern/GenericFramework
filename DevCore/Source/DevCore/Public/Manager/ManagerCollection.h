#pragma once
#include "CoreManager.h"


class UCoreManager;

class DEVCORE_API FManagerCollection
{
public:
	static FManagerCollection* Instance;
	static FManagerCollection* Get();

public:
	void RegisterManager(UCoreManager* InCoreManager);
	TArray<UCoreManager*> GetManagers() { return Managers; }

	template <typename ManagerClass>
	ManagerClass* GetManager()
	{
		for (const auto& Manager : Managers)
		{
			if (Manager->GetClass() == ManagerClass::StaticClass() || Manager->GetClass()->IsChildOf(ManagerClass::StaticClass()))
			{
				return Cast<ManagerClass>(Manager);
			}
		}
		return nullptr;
	}

protected:
	TArray<UCoreManager*> Managers;
};
