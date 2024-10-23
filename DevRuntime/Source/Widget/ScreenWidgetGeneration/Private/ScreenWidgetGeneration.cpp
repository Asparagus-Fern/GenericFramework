#include "ScreenWidgetGeneration.h"

#include "ScreenWidgetManager.h"

#define LOCTEXT_NAMESPACE "FScreenWidgetGenerationModule"

void FScreenWidgetGenerationModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FScreenWidgetGenerationModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FScreenWidgetGenerationModule, ScreenWidgetGeneration)
