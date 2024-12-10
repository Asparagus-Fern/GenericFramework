#include "WorldWidgetGeneration.h"

#include "WorldWidgetManager.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetGenerationModule"

void FWorldWidgetGenerationModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FWorldWidgetGenerationModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldWidgetGenerationModule, WorldWidgetGeneration)
