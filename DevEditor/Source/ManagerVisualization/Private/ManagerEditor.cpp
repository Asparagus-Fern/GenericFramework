// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerEditor.h"

#include "DevEdCoreStyle.h"
#include "LevelEditor.h"
#include "ManagerEditorCommands.h"
#include "ToolMenuSection.h"
#include "Manager/ManagerSubsystem.h"
#include "Slate/SManagerEditor.h"

#define LOCTEXT_NAMESPACE "UManagerEditor"

FName UManagerEditor::ManagerEditorTabName = "ManagerEditor";

UManagerEditor::UManagerEditor()
{
}

void UManagerEditor::NativeOnCreate()
{
	Super::NativeOnCreate();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UManagerEditor::OnLevelEditorCreated);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ManagerEditorTabName, FOnSpawnTab::CreateUObject(this, &UManagerEditor::SpawnManagerEditorTab))
		.SetDisplayName(LOCTEXT("ManagerEditorTitle", "Manager Editor"))
		.SetTooltipText(LOCTEXT("ManagerEditorTooltip", "Open Manager Editor Window."))
		.SetIcon(FSlateIcon(FDevEdCoreStyle::GetStyleSetName(), "Manager.ToolbarButton.Small"));
}

void UManagerEditor::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ManagerEditorTabName);
}

FText UManagerEditor::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Manager Editor");
}

bool UManagerEditor::DoesSupportWorldType(EWorldType::Type InWorldType)
{
	return Super::DoesSupportWorldType(InWorldType) || InWorldType == EWorldType::Editor;
}

void UManagerEditor::InitCommandList(TSharedPtr<FUICommandList>& InCommandList)
{
	const FManagerEditorCommands& Commands = FManagerEditorCommands::Get();

	InCommandList->MapAction(Commands.OpenManagerEditor, FExecuteAction::CreateStatic(&UManagerEditor::OpenManagerEditor));
}

void UManagerEditor::ExtendToolBar(FToolMenuSection& InSection)
{
	InSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			FManagerEditorCommands::Get().OpenManagerEditor,
			FText::GetEmpty(),
			TAttribute<FText>(),
			FSlateIcon(FDevEdCoreStyle::GetStyleSetName(), "Manager.ToolbarButton", "Manager.ToolbarButton.Small")
		)
	);
}

void UManagerEditor::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	ManagerListView = FListViewBase<FManagerListViewInfo, FManagerListViewItem>::New();
	for (const auto& Manager : UManagerSubsystem::Get()->GetManagers())
	{
		ManagerListView->ListViewMap.Add(MakeShareable(new FManagerListViewInfo(Manager)), MakeShareable(new FManagerListViewItem()));
	}
}

void UManagerEditor::OpenManagerEditor()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ManagerEditorTabName);
	DEBUG(Debug_Manager, Log, TEXT("Open Manager Editor"))
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
