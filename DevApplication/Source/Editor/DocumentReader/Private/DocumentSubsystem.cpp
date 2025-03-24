// Copyright ChenTaiye 2025. All Rights Reserved.


#include "DocumentSubsystem.h"

#include "DevCoreStyle.h"
#include "DevFrameworkEdSubsystem.h"

#define LOCTEXT_NAMESPACE "UFastSwitchLanguage"

void UDocumentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FDevFrameworkDelegate::OnToolBarSectionExtend.AddUObject(this, &UDocumentSubsystem::OnToolBarSectionExtend);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DocumentTabName, FOnSpawnTab::CreateUObject(this, &UDocumentSubsystem::HandleSpawnDocumentTab))
		.SetDisplayName(LOCTEXT("DocumentTabTitle", "Developer Document"))
		.SetMenuType(ETabSpawnerMenuType::Hidden)
		.SetIcon(FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Developer.ReadMe", "Developer.ReadMe.Small"));
}

void UDocumentSubsystem::Deinitialize()
{
	Super::Deinitialize();
	FDevFrameworkDelegate::OnToolBarSectionExtend.RemoveAll(this);
}

void UDocumentSubsystem::OnToolBarSectionExtend(FToolMenuSection& InToolMenuSection)
{
	InToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			"ReadMe",
			FUIAction(FExecuteAction::CreateUObject(this, &UDocumentSubsystem::OpenDucument)),
			TAttribute<FText>(),
			LOCTEXT("ReadMe_ToolTip", "Open Ducument About DevPlugin"),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Developer.ReadMe", "Developer.ReadMe.Small")
		)
	);
}

void UDocumentSubsystem::OpenDucument()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DocumentTabName);
}

TSharedRef<SDockTab> UDocumentSubsystem::HandleSpawnDocumentTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SWidget> SettingsEditor = SNullWidget::NullWidget;

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SettingsEditor
		];
}

#undef LOCTEXT_NAMESPACE
