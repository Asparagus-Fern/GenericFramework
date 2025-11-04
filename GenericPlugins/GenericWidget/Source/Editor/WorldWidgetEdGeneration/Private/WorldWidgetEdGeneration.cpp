#include "WorldWidgetEdGeneration.h"

#include "WorldWidgetEdSubsystem.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetEdGenerationModule"

void FWorldWidgetEdGenerationModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FWorldWidgetEdGenerationModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FWorldWidgetEdGenerationModule, WorldWidgetEdGeneration)
