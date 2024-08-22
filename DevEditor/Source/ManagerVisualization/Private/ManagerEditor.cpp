// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerEditor.h"

#include "DevCoreStyle.h"
#include "LevelEditor.h"
#include "ManagerEditorCommands.h"
#include "ToolMenuSection.h"
#include "Slate/SManagerEditor.h"

#define LOCTEXT_NAMESPACE "UManagerEditor"

FName UManagerEditor::ManagerEditorTabName = "ManagerEditor";

bool UManagerEditor::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UManagerEditor::NativeOnCreate()
{
	Super::NativeOnCreate();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UManagerEditor::OnLevelEditorCreated);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ManagerEditorTabName, FOnSpawnTab::CreateUObject(this, &UManagerEditor::SpawnManagerEditorTab))
		.SetDisplayName(LOCTEXT("ManagerEditorTitle", "Manager Editor"))
		.SetTooltipText(LOCTEXT("ManagerEditorTooltip", "Open Manager Editor Window."))
		.SetIcon(FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Manager.ToolbarButton.Small"));
}

void UManagerEditor::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ManagerEditorTabName);
}

void UManagerEditor::InitCommandList(TSharedPtr<FUICommandList>& InCommandList)
{
	const FManagerEditorCommands& Commands = FManagerEditorCommands::Get();

	InCommandList->MapAction(Commands.OpenManagerEditor, FExecuteAction::CreateStatic(&UManagerEditor::OpenManagerEditor));
}

void UManagerEditor::ExtendToolBar_Implementation(FToolMenuSection& InSection)
{
	IManagerEdInterface::ExtendToolBar_Implementation(InSection);

	InSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			FManagerEditorCommands::Get().OpenManagerEditor,
			FText::GetEmpty(),
			TAttribute<FText>(),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Manager.ToolbarButton", "Manager.ToolbarButton.Small")
		)
	);
}

void UManagerEditor::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	ManagerListView = FListViewBase<FManagerListViewInfo, FManagerListViewItem>::New();
	// for (const auto& Manager : UManagerSubsystem::Get()->GetManagers())
	// {
	// 	ManagerListView->ListViewMap.Add(MakeShareable(new FManagerListViewInfo(Manager)), MakeShareable(new FManagerListViewItem()));
	// }
}

void UManagerEditor::OpenManagerEditor()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ManagerEditorTabName);
	LOG(Debug_Manager, Log, TEXT("Open Manager Editor"))
}

TSharedRef<SDockTab> UManagerEditor::SpawnManagerEditorTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> DockTab = SAssignNew(ManagerEditorTab, SDockTab)
		.TabRole(ETabRole::NomadTab)
		.OnTabClosed_UObject(this, &UManagerEditor::OnManagerEditorClose);

	SAssignNew(ManagerEditorPtr, SManagerEditor, DockTab);
	ManagerEditorPtr->NativeOnCreate();

	DockTab->SetContent(ManagerEditorPtr.ToSharedRef());

	return DockTab;
}

void UManagerEditor::OnManagerEditorClose(TSharedRef<SDockTab> InDockTab)
{
	ManagerEditorPtr->NativeOnDestroy();
}

#undef LOCTEXT_NAMESPACE
