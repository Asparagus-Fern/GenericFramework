#include "ManagerSettingCommands.h"

#include "DevCoreStyle.h"

#define LOCTEXT_NAMESPACE "FManagerEditorCommands"

FManagerSettingCommands::FManagerSettingCommands()
	: TCommands<FManagerSettingCommands>(
		"ManagerEditorCommands",
		LOCTEXT("Tooltip", "Manager Editor"),
		NAME_None,
		FDevCoreStyle::GetStyleSetName()
	)
{
}

void FManagerSettingCommands::RegisterCommands()
{
	UI_COMMAND(OpenManagerSetting, "OpenManagerEditor", "Open Manager Editor", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
