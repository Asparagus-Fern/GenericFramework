#include "ManagerVisualization.h"

#include "ManagerEditor.h"
#include "ManagerEditorCommands.h"

#define LOCTEXT_NAMESPACE "FManagerVisualizationModule"

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
