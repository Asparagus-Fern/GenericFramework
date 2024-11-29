#include "ExtendEdMode.h"

#include "DevEdModeCommands.h"

#define LOCTEXT_NAMESPACE "FExtendEdModeModule"

void FExtendEdModeModule::StartupModule()
{
	FDevEdModeCommands::Register();
}

void FExtendEdModeModule::ShutdownModule()
{
	FDevEdModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FExtendEdModeModule, ExtendEdMode)
