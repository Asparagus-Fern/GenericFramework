#include "ActiveNodeSystem.h"

#include "ActiveNodeManager.h"

#define LOCTEXT_NAMESPACE "FActiveNodeSystemModule"

void FActiveNodeSystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UActiveNodeManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FActiveNodeSystemModule, ActiveNodeSystem)
