#pragma once

#include "Manager/CoreManager.h"

class FStaticFunctions_Manager
{
public:
	template <typename InterfaceClass>
	static TArray<InterfaceClass*> GetManagersWithInterface()
	{
		TArray<InterfaceClass*> Managers;
		for (const auto& Manager : GEngine->GetEngineSubsystemArray<UCoreManager>())
		{
			if (Manager->GetClass()->ImplementsInterface(InterfaceClass::UClassType::StaticClass()))
			{
				Managers.Add(Cast<InterfaceClass>(Manager));
			}
		}
		return Managers;
	}

	template <typename ManagerClass>
	static void ProcessManagerInterface(const TFunctionRef<void(UCoreManager* InManager)>& Exec)
	{
		TArray<ManagerClass*> Managers = GEngine->GetEngineSubsystemArray<ManagerClass>();
		for (auto& Manager : Managers)
		{
			Exec(Manager);
		}
	}
};
