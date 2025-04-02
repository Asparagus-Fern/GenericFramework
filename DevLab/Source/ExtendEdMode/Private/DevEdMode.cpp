#include "DevEdMode.h"

#include "DevEdModeCommands.h"
#include "DevEdModeToolkit.h"
#include "InteractiveToolManager.h"
#include "Tool/DrawZoneShapeTool.h"

#define LOCTEXT_NAMESPACE "UDevEdMode"

FEditorModeID UDevEdMode::DevCommonEdModeId = "DevEdMode";

UDevEdMode::UDevEdMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	Info = FEditorModeInfo(
		DevCommonEdModeId,
		LOCTEXT("DisplayName", "DevEdMode"),
		FSlateIcon("ModelingToolsStyle", "LevelEditor.ModelingToolsMode", "LevelEditor.ModelingToolsMode.Small"),
		true
	);
}

void UDevEdMode::Enter()
{
	Super::Enter();

	const FDevEdModeCommands& DevCommonEdCommands = FDevEdModeCommands::Get();

	RegisterTool(DevCommonEdCommands.DrawZoneShape, TEXT("DrawZoneShape"), NewObject<UDrawZoneShapeToolBuilder>(this));

	GetToolManager()->SelectActiveToolType(EToolSide::Left, TEXT("DevEdModeTool"));
}

void UDevEdMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FDevEdModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UDevEdMode::GetModeCommands() const
{
	return FDevEdModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
