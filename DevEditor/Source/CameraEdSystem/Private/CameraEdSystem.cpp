#include "CameraEdSystem.h"

#include "CameraEdManager.h"

#define LOCTEXT_NAMESPACE "FCameraEdSystemModule"

void FCameraEdSystemModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonEdModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("CameraSystem");
}

void FCameraEdSystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonEdModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UCameraEdManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCameraEdSystemModule, CameraEdSystem)
