#include "WorldPartition.h"

#define LOCTEXT_NAMESPACE "FWorldPartitionModule"

void FWorldPartitionModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FWorldPartitionModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldPartitionModule, WorldPartition)
