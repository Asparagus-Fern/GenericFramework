#include "DevEdCore.h"

#include "AssetToolsModule.h"
#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsEditorModel.h"
#include "ISettingsEditorModule.h"
#include "ISettingsModule.h"
#include "Manager/GlobalManagerSetting.h"
#include "Manager/ManagerSetting/ManagerSettingCommands.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

static const FName ManagerSettingsTabName("ManagerSettings");

void FDevEdCoreModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();
	FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory("DevFramework", LOCTEXT("DisplayName", "DevFramework"));

	/* 创建管理类的设置 */
	{
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

		if (SettingsModule != nullptr)
		{
			RegisterManagerSettings(*SettingsModule);
			SettingsModule->RegisterViewer("Manager", *this);
		}

		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ManagerSettingsTabName, FOnSpawnTab::CreateRaw(this, &FDevEdCoreModule::HandleSpawnSettingsTab))
			.SetDisplayName(LOCTEXT("ProjectSettingsTabTitle", "Manager Settings"))
			.SetMenuType(ETabSpawnerMenuType::Hidden)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "ProjectSettings.TabIcon"));
	}
}

void FDevEdCoreModule::ShowSettings(const FName& CategoryName, const FName& SectionName)
{
	FGlobalTabmanager::Get()->TryInvokeTab(ManagerSettingsTabName);
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

void FDevEdCoreModule::RegisterManagerSettings(ISettingsModule& SettingsModule)
{
	SettingsModule.RegisterSettings
	(
		"Manager", "Manager(Global)", "Global",
		LOCTEXT("ManagerGlobalSettingsSettingsName", "Manager Global Settings"),
		LOCTEXT("ManagerGlobalSettingsDescription", "Manager Global Settings"),
		GetMutableDefault<UGlobalManagerSetting>()
	);
}

TSharedRef<SDockTab> FDevEdCoreModule::HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SWidget> SettingsEditor = SNullWidget::NullWidget;
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		const ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Manager");

		if (SettingsContainer.IsValid())
		{
			ISettingsEditorModule& SettingsEditorModule = FModuleManager::GetModuleChecked<ISettingsEditorModule>("SettingsEditor");
			const ISettingsEditorModelRef SettingsEditorModel = SettingsEditorModule.CreateModel(SettingsContainer.ToSharedRef());

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

void FDevEdCoreModule::RegisterCommand()
{
	ICommonEdModuleInterface::RegisterCommand();
	FManagerSettingCommands::Register();
}

void FDevEdCoreModule::RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions)
{
	ICommonEdModuleInterface::RegisterAssetActions(OutAssetActions);
}

void FDevEdCoreModule::UnRegisterCommand()
{
	ICommonEdModuleInterface::UnRegisterCommand();
	FManagerSettingCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevEdCoreModule, DevEdCore)
