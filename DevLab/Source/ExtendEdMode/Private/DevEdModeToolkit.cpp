#include "DevEdModeToolkit.h"

#include "EdModeInteractiveToolsContext.h"
#include "InteractiveTool.h"
#include "InteractiveToolManager.h"
#include "SPrimaryButton.h"
#include "Tools/UEdMode.h"

#define LOCTEXT_NAMESPACE "FDevEdModeToolkit"

void FDevEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	FModeToolkit::Init(InitToolkitHost);
}

void FDevEdModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}

FName FDevEdModeToolkit::GetToolkitFName() const
{
	return "DevEdModeToolkit";
}

FText FDevEdModeToolkit::GetToolkitName() const
{
	return LOCTEXT("DisplayName", "DevEdMode Toolkit");
}

void FDevEdModeToolkit::OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolStarted(Manager, Tool);

	ViewportWidget = MakeEdModeViewportWidget();
	GetToolkitHost()->AddViewportOverlayWidget(ViewportWidget.ToSharedRef());
}

void FDevEdModeToolkit::OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolEnded(Manager, Tool);

	if (IsHosted())
	{
		GetToolkitHost()->RemoveViewportOverlayWidget(ViewportWidget.ToSharedRef());
	}
}

TSharedRef<SWidget> FDevEdModeToolkit::MakeEdModeViewportWidget()
{
	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		.Padding(FMargin(0.0f, 0.0f, 0.f, 15.f))
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("EditorViewport.OverlayBrush"))
			.Padding(8.f)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.f, 0.f, 8.f, 0.f))
				[
					SNew(STextBlock)
					.Text(GetScriptableEditorMode()->GetToolManager(EToolsContextScope::EdMode)->GetActiveTool(EToolSide::Left)->GetToolInfo().ToolDisplayName)
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(0.0, 0.f, 2.f, 0.f))
				[
					SNew(SPrimaryButton)
					.Text(LOCTEXT("OverlayAccept", "Accept"))
					.ToolTipText(LOCTEXT("OverlayAcceptTooltip", "Accept/Commit the results of the active Tool [Enter]"))
					.OnClicked_Lambda([this]()
						{
							GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->EndTool(EToolShutdownType::Accept);
							return FReply::Handled();
						}
					)
					.IsEnabled_Lambda([this]() { return GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->CanAcceptActiveTool(); })
					.Visibility_Lambda([this]() { return GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->ActiveToolHasAccept() ? EVisibility::Visible : EVisibility::Collapsed; })
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(2.0, 0.f, 0.f, 0.f))
				[
					SNew(SButton)
					.Text(LOCTEXT("OverlayCancel", "Cancel"))
					.ToolTipText(LOCTEXT("OverlayCancelTooltip", "Cancel the active Tool [Esc]"))
					.HAlign(HAlign_Center)
					.OnClicked_Lambda([this]()
						{
							GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->EndTool(EToolShutdownType::Cancel);
							return FReply::Handled();
						}
					)
					.IsEnabled_Lambda([this]() { return GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->CanCancelActiveTool(); })
					.Visibility_Lambda([this]() { return GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->ActiveToolHasAccept() ? EVisibility::Visible : EVisibility::Collapsed; })
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
