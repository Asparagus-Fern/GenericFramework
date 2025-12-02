// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Tools/OpenDeveloperSetting.h"

#include "DevCoreStyle.h"
#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsEditorModel.h"
#include "ISettingsEditorModule.h"
#include "ISettingsModule.h"
#include "Settings/GenericGlobalSettings.h"
#include "Subsystem/GenericFrameworkEdSubsystem.h"

#define LOCTEXT_NAMESPACE "FApplicationEditorModule"

void UOpenDeveloperSetting::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericFrameworkEdSubsystem::OnToolBarSectionExtend.AddUObject(this, &UOpenDeveloperSetting::RegisterToolBarGenericFrameworkSetting);

	/* Create Generic Framework Settings */
	{
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			SettingsModule->RegisterSettings
			(
				"GenericFramework", "Global", "Global",
				LOCTEXT("ManagerGlobalSettingsSettingsName", "Manager"),
				LOCTEXT("ManagerGlobalSettingsDescription", "Manager Settings"),
				GetMutableDefault<UGenericGlobalSettings>()
			);

			SettingsModule->RegisterViewer("GenericFramework", *this);
		}

		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GenericFrameworkSettingsTabName, FOnSpawnTab::CreateUObject(this, &UOpenDeveloperSetting::HandleSpawnSettingsTab))
			.SetDisplayName(LOCTEXT("GenericFrameworkSettingsTabTitle", "Generic Framework Settings"))
			.SetMenuType(ETabSpawnerMenuType::Hidden)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "ProjectSettings.TabIcon"));
	}
}

void UOpenDeveloperSetting::Deinitialize()
{
	Super::Deinitialize();

	UGenericFrameworkEdSubsystem::OnToolBarSectionExtend.RemoveAll(this);

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("GenericFramework", "Global", "Global");
		SettingsModule->UnregisterViewer("GenericFramework");
	}
}

void UOpenDeveloperSetting::ShowSettings(const FName& CategoryName, const FName& SectionName)
{
	FGlobalTabmanager::Get()->TryInvokeTab(GenericFrameworkSettingsTabName);
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
		const ISettingsContainerPtr DeveloperSettingsContainer = SettingsModule->GetContainer("GenericFramework");

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

void UOpenDeveloperSetting::RegisterToolBarGenericFrameworkSetting(FToolMenuSection& ToolMenuSection)
{
	ToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			"OpenGenericFrameworkSetting",
			FUIAction(FExecuteAction::CreateUObject(this, &UOpenDeveloperSetting::OpenToolBarGenericFrameworkSetting)),
			TAttribute<FText>(),
			LOCTEXT("OpenGenericFrameworkSetting_ToolTip", "Click To Open Generic Framework Settings"),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Developer.DeveloperSetting", "Developer.DeveloperSetting.Small")
		)
	);
}

void UOpenDeveloperSetting::OpenToolBarGenericFrameworkSetting()
{
	ISettingsModule& SettingsModule = FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.ShowViewer("GenericFramework", "Global", "Global");
}

#undef LOCTEXT_NAMESPACE
