#include "CameraSystem.h"

#include "CameraManager.h"

#define LOCTEXT_NAMESPACE "FCameraSystemModule"

void FCameraSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCameraSystemModule, CameraSystem)


