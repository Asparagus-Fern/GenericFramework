// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Tools/OpenDeveloperSetting.h"

#include "DevCoreStyle.h"
#include "DevFrameworkEdSubsystem.h"
#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsEditorModel.h"
#include "ISettingsEditorModule.h"
#include "ISettingsModule.h"
#include "Manager/ManagerSettings.h"

#define LOCTEXT_NAMESPACE "UOpenDeveloperSetting"

void UOpenDeveloperSetting::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FDevFrameworkDelegate::OnToolBarSectionExtend.AddUObject(this, &UOpenDeveloperSetting::RegisterToolBarDeveloperSetting);

	/* Create Developer Settings */
	{
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			SettingsModule->RegisterSettings
			(
				"Developer", "Global", "Global",
				LOCTEXT("ManagerGlobalSettingsSettingsName", "Manager"),
				LOCTEXT("ManagerGlobalSettingsDescription", "Manager Settings"),
				GetMutableDefault<UManagerSettings>()
			);

			SettingsModule->RegisterViewer("Developer", *this);
		}

		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DeveloperSettingsTabName, FOnSpawnTab::CreateUObject(this, &UOpenDeveloperSetting::HandleSpawnSettingsTab))
			.SetDisplayName(LOCTEXT("ProjectSettingsTabTitle", "Developer Settings"))
			.SetMenuType(ETabSpawnerMenuType::Hidden)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "ProjectSettings.TabIcon"));
	}
}

void UOpenDeveloperSetting::Deinitialize()
{
	Super::Deinitialize();

	FDevFrameworkDelegate::OnToolBarSectionExtend.RemoveAll(this);

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Developer", "Global", "Global");
		SettingsModule->UnregisterViewer("Developer");
	}
}

void UOpenDeveloperSetting::ShowSettings(const FName& CategoryName, const FName& SectionName)
{
	FGlobalTabmanager::Get()->TryInvokeTab(DeveloperSettingsTabName);
	const ISettingsEditorModelPtr SettingsEditorModel = SettingsEditorModelPtr.Pin();

	if (SettingsEditorModel.IsValid())
	{
		const ISettingsCategoryPtr Category = SettingsEditorModel->GetSettingsContainer()->GetCategory(CategoryName);

		if (Category.IsValid())
		{
			SettingsEditorModel->SelectSection(Category->GetSection(SectionName));
		}
	}
}

TSharedRef<SDockTab> UOpenDeveloperSetting::HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SWidget> SettingsEditor = SNullWidget::NullWidget;
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		const ISettingsContainerPtr DeveloperSettingsContainer = SettingsModule->GetContainer("Developer");

		if (DeveloperSettingsContainer.IsValid())
		{
			ISettingsEditorModule& SettingsEditorModule = FModuleManager::GetModuleChecked<ISettingsEditorModule>("SettingsEditor");
			const ISettingsEditorModelRef SettingsEditorModel = SettingsEditorModule.CreateModel(DeveloperSettingsContainer.ToSharedRef());

			SettingsEditor = SettingsEditorModule.CreateEditor(SettingsEditorModel);
			SettingsEditorModelPtr = SettingsEditorModel;
		}
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SettingsEditor
		];
}

void UOpenDeveloperSetting::RegisterToolBarDeveloperSetting(FToolMenuSection& ToolMenuSection)
{
	ToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			"OpenDeveloperSetting",
			FUIAction(FExecuteAction::CreateUObject(this, &UOpenDeveloperSetting::OpenToolBarManagerSetting)),
			TAttribute<FText>(),
			LOCTEXT("OpenDeveloperSetting_ToolTip", "Click To Open Developer Settings"),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Developer.DeveloperSetting", "Developer.DeveloperSetting.Small")
		)
	);
}

void UOpenDeveloperSetting::OpenToolBarManagerSetting()
{
	ISettingsModule& SettingsModule = FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.ShowViewer("Developer", "Global", "Global");
}

#undef LOCTEXT_NAMESPACE
