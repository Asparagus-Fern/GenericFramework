#include "CameraSystem.h"

#include "CameraManager.h"

#define LOCTEXT_NAMESPACE "FCameraSystemModule"

void FCameraSystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UCameraManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCameraSystemModule, CameraSystem)
