#include "LevelStreaming.h"

#include "LevelStreamingManager.h"

#define LOCTEXT_NAMESPACE "FLevelStreamingModule"

void FLevelStreamingModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("DevCore");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLevelStreamingModule, LevelStreaming)
