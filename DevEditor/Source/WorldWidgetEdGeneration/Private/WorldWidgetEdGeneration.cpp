#include "WorldWidgetEdGeneration.h"

#include "WorldWidgetEdManager.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetEdGenerationModule"

void FWorldWidgetEdGenerationModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonEdModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("WorldWidgetGeneration");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FWorldWidgetEdGenerationModule, WorldWidgetEdGeneration)
