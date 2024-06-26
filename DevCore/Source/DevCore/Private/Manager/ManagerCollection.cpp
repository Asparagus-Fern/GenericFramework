#include "Manager/ManagerCollection.h"

#include "Manager/CoreManager.h"

FManagerCollection* FManagerCollection::Instance = nullptr;

FManagerCollection* FManagerCollection::Get()
{
	if (!Instance)
	{
		Instance = new FManagerCollection();
	}
	return Instance;
}

void FManagerCollection::RegisterManager(UCoreManager* InCoreManager)
{
	if (!IsValid(InCoreManager))
	{
		return;
	}

	if (!Managers.Contains(InCoreManager))
	{
		TArray<UCoreManager*> TempManager = Managers;
		for (auto Manager : TempManager)
		{
			if (InCoreManager->GetClass()->IsChildOf(Manager->GetClass()))
			{
				Managers.Remove(Manager);
			}
		}

		Managers.Add(InCoreManager);
		DEBUG(Debug_Manager, Log, TEXT("On Register : %s"), *InCoreManager->GetName());
	}
}
