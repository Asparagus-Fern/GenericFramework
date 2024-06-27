#include "WorldWidgetGeneration.h"

#include "WorldWidgetManager.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetGenerationModule"

void FWorldWidgetGenerationModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);

	InDependentModuleName.Add("ScreenWidgetGeneration");
}

void FWorldWidgetGenerationModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UWorldWidgetManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldWidgetGenerationModule, WorldWidgetGeneration)
