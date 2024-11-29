#include "RoadNetworkSystem.h"

#define LOCTEXT_NAMESPACE "FRoadNetworkSystemModule"

void FRoadNetworkSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FRoadNetworkSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRoadNetworkSystemModule, RoadNetworkSystem)
