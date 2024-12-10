#include "CameraEdSystem.h"

#include "CameraEdManager.h"

#define LOCTEXT_NAMESPACE "FCameraEdSystemModule"

void FCameraEdSystemModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FCameraEdSystemModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCameraEdSystemModule, CameraEdSystem)
