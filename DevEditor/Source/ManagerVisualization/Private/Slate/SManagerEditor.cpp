// Fill out your copyright notice in the Description page of Project Settings.

#include "Slate/SManagerEditor.h"

#include "DevEdCoreStyle.h"
#include "LevelEditorActions.h"
#include "ManagerEditor.h"
#include "ManagerEditorType.h"
#include "SlateOptMacros.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "SManagerEditor"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FName SManagerEditor::ManagerEditorToolBarName = "ManagerEditor.ManagerEditorToolBar";
FName SManagerEditor::ManagerListTabID = "ManagerListTab";
FName SManagerEditor::ManagerDetailTabID = "ManagerDetailTab";

void SManagerEditor::Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& InDockTab)
{
	ParentDockTab = InDockTab;
	TabManager = FGlobalTabmanager::Get()->NewTabManager(InDockTab);
	ManagerListViewItems = UManagerEditor::Get()->GetManagerListView()->GetItems();

	TabManager->RegisterTabSpawner(ManagerListTabID, FOnSpawnTab::CreateSP(this, &SManagerEditor::SpawnManagerListTab))
	.SetDisplayName(LOCTEXT("ManagerListTitle", "Manager List"))
	.SetIcon(FSlateIcon(FDevEdCoreStyle::GetStyleSetName(), "Manager.ToolbarButton.Small"));

	TabManager->RegisterTabSpawner(ManagerDetailTabID, FOnSpawnTab::CreateSP(this, &SManagerEditor::SpawnManagerDetailTab))
	.SetDisplayName(LOCTEXT("ManagerDetailTitle", "Manager Detail"))
	.SetIcon(FSlateIcon(FDevEdCoreStyle::GetStyleSetName(), "Manager.ToolbarButton.Small"));

	TSharedRef<FTabManager::FLayout> Layout = []()
	{
		return FTabManager::NewLayout("ManagerEditorLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(.35f)
				->AddTab(ManagerListTabID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(.65f)
				->AddTab(ManagerDetailTabID, ETabState::OpenedTab)
			)
		);
	}();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Background"))
			[
				RegisterManagerEditorToolBar()
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			TabManager->RestoreFrom(Layout, InDockTab->GetParentWindow()).ToSharedRef()
		]
	];
}

void SManagerEditor::NativeOnCreate()
{
}

void SManagerEditor::NativeOnDestroy()
{
	if (ParentDockTab.IsValid())
	{
		TabManager->UnregisterTabSpawner(ManagerListTabID);
		TabManager->UnregisterTabSpawner(ManagerDetailTabID);
	}
}

TSharedRef<SWidget> SManagerEditor::RegisterManagerEditorToolBar()
{
	const FToolMenuContext Context;
	UToolMenu* ToolMenu = UToolMenus::Get()->RegisterMenu(ManagerEditorToolBarName, NAME_None, EMultiBoxType::SlimHorizontalToolBar);
	UToolMenus::Get()->GenerateMenu(ManagerEditorToolBarName, Context);

	/* File */
	{
		FToolMenuSection& FileSection = ToolMenu->AddSection("File");

		/* Save */
		FileSection.AddEntry
		(
			FToolMenuEntry::InitToolBarButton
			(
				FLevelEditorCommands::Get().Save,
				FText::GetEmpty(),
				TAttribute<FText>(),
				FSlateIcon(FAppStyle::GetAppStyleSetName(), "AssetEditor.SaveAsset"),
				NAME_None,
				FName("SaveAllLevels")
			)
		);
	}

	return UToolMenus::Get()->GenerateWidget(ToolMenu);
}

TSharedRef<SDockTab> SManagerEditor::SpawnManagerListTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> DockTab = SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			SNew(SListView<FManagerListViewItemPtr>)
			.ListItemsSource(&ManagerListViewItems)
			.OnGenerateRow(this, &SManagerEditor::OnGenerateRow)
			.OnSelectionChanged(this, &SManagerEditor::OnSelectionChanged)
		];

	return DockTab;
}

TSharedRef<SDockTab> SManagerEditor::SpawnManagerDetailTab(const FSpawnTabArgs& Args)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bAllowSearch = true;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(nullptr);

	TSharedRef<SDockTab> DockTab = SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			DetailsView->AsShared()
		];

	return DockTab;
}

TSharedRef<ITableRow> SManagerEditor::OnGenerateRow(FManagerListViewItemPtr InItem, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(STableRow< FManagerListViewItemPtr>, Owner)
		[
			InItem->MakeWidget()
		];
}

void SManagerEditor::OnSelectionChanged(FManagerListViewItemPtr InItem, ESelectInfo::Type SelectInfo)
{
	if (DetailsView.IsValid() && InItem.IsValid())
	{
		FManagerListViewInfoPtr ManagerListViewInfo = UManagerEditor::Get()->GetManagerListView()->GetInfo(InItem.ToSharedRef());
		DetailsView->SetObject(ManagerListViewInfo->CoreManager);
	}
	else
	{
		DetailsView->SetObject(nullptr);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
