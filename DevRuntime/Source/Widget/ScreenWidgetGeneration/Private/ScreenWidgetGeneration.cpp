#include "ScreenWidgetGeneration.h"

#include "ScreenWidgetManager.h"

#define LOCTEXT_NAMESPACE "FScreenWidgetGenerationModule"

void FScreenWidgetGenerationModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FScreenWidgetGenerationModule, ScreenWidgetGeneration)
