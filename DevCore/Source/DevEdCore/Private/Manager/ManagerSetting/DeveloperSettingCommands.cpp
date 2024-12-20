#include "DeveloperSettingCommands.h"

#include "DevCoreStyle.h"

#define LOCTEXT_NAMESPACE "FManagerEditorCommands"

FDeveloperSettingCommands::FDeveloperSettingCommands()
	: TCommands<FDeveloperSettingCommands>(
		"ManagerEditorCommands",
		LOCTEXT("Tooltip", "Manager Editor"),
		NAME_None,
		FDevCoreStyle::GetStyleSetName()
	)
{
}

void FDeveloperSettingCommands::RegisterCommands()
{
	UI_COMMAND(OpenDeveloperSetting, "OpenDeveloperSettings", "Open Developer Settings", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
