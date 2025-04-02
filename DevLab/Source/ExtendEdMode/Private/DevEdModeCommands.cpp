#include "DevEdModeCommands.h"

#include "DevCoreStyle.h"

#define LOCTEXT_NAMESPACE "FDevEdModeCommands"

FDevEdModeCommands::FDevEdModeCommands()
	: TCommands<FDevEdModeCommands>(
		"DevEdModeCommands",
		LOCTEXT("Tooltip", "Dev Editor Mode"),
		NAME_None,
		FDevCoreStyle::GetStyleSetName()
	)
{
}

void FDevEdModeCommands::RegisterCommands()
{
	TArray<TSharedPtr<FUICommandInfo>>& EdModeCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(DrawZoneShape, "DrawZoneShape", "Draw ZoneShape Actor", EUserInterfaceActionType::RadioButton, FInputChord());
	EdModeCommands.Add(DrawZoneShape);
}

#undef LOCTEXT_NAMESPACE
