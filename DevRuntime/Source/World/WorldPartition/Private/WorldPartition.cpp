#include "WorldPartition.h"

#define LOCTEXT_NAMESPACE "FWorldPartitionModule"

void FWorldPartitionModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("DevCore");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldPartitionModule, WorldPartition)
