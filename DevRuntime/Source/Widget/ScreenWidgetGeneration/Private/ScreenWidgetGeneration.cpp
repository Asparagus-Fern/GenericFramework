#include "ScreenWidgetGeneration.h"

#include "ScreenWidgetManager.h"

#define LOCTEXT_NAMESPACE "FScreenWidgetGenerationModule"

void FScreenWidgetGenerationModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UScreenWidgetManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FScreenWidgetGenerationModule, ScreenWidgetGeneration)
