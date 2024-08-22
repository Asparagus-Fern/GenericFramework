#include "ManagerEditorCommands.h"

#include "DevCoreStyle.h"

#define LOCTEXT_NAMESPACE "FManagerEditorCommands"

FManagerEditorCommands::FManagerEditorCommands()
	: TCommands<FManagerEditorCommands>(
		"ManagerEditorCommands",
		LOCTEXT("Tooltip", "Manager Editor"),
		NAME_None,
		FDevCoreStyle::GetStyleSetName()
	)
{
}

void FManagerEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenManagerEditor, "OpenManagerEditor", "Open Manager Editor", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
