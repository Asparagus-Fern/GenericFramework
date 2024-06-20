#include "WorldWidgetGeneration.h"

#include "WorldWidgetManager.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetGenerationModule"

void FWorldWidgetGenerationModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FWorldWidgetGenerationModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

void FWorldWidgetGenerationModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);

	InDependentModuleName.Add("ScreenWidgetGeneration");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldWidgetGenerationModule, WorldWidgetGeneration)
