#include "ManagerVisualization.h"

#include "ManagerEditor.h"
#include "ManagerEditorCommands.h"

#define LOCTEXT_NAMESPACE "FManagerVisualizationModule"

void FManagerVisualizationModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonEdModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UManagerEditor::StaticClass());
}

void FManagerVisualizationModule::RegisterCommand()
{
	FManagerEditorCommands::Register();
}

void FManagerVisualizationModule::UnRegisterCommand()
{
	FManagerEditorCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FManagerVisualizationModule, ManagerVisualization)
