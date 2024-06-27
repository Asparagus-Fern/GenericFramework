#include "LevelStreaming.h"

#include "LevelStreamingManager.h"

#define LOCTEXT_NAMESPACE "FLevelStreamingModule"

void FLevelStreamingModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("DevCore");
}

void FLevelStreamingModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(ULevelStreamingManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLevelStreamingModule, LevelStreaming)
