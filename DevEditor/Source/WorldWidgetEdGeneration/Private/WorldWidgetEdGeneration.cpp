#include "WorldWidgetEdGeneration.h"

#include "WorldWidgetEdManager.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetEdGenerationModule"

void FWorldWidgetEdGenerationModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonEdModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("WorldWidgetGeneration");
}

void FWorldWidgetEdGenerationModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonEdModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UWorldWidgetEdManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FWorldWidgetEdGenerationModule, WorldWidgetEdGeneration)
