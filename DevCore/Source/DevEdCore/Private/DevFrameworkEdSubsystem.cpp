// Fill out your copyright notice in the Description page of Project Settings.


#include "DevFrameworkEdSubsystem.h"

#include "DevCoreStyle.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "Manager/ManagerSetting/DeveloperSettingCommands.h"

#define LOCTEXT_NAMESPACE "UManagerEdSubsystem"

FName UDevFrameworkEdSubsystem::MenuBarSectionName = "DevEdMenuBar";
FName UDevFrameworkEdSubsystem::ToolBarSectionName = "DevEdTooBar";

UDevFrameworkEdSubsystem* UDevFrameworkEdSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UDevFrameworkEdSubsystem>();
}

void UDevFrameworkEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UDevFrameworkEdSubsystem::OnLevelEditorCreated);

	OnCommandListInitialize.AddUObject(this, &UDevFrameworkEdSubsystem::RegisterToolBarDeveloperSettingCommand);
	OnToolBarSectionExtend.AddUObject(this, &UDevFrameworkEdSubsystem::RegisterToolBarDeveloperSetting);
}

void UDevFrameworkEdSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().RemoveAll(this);

	OnCommandListInitialize.RemoveAll(this);
	OnToolBarSectionExtend.RemoveAll(this);
}

void UDevFrameworkEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	CommandList = MakeShareable(new FUICommandList);
	OnCommandListInitialize.Broadcast(CommandList);

	RegisterMenuBar();

	RegisterToolBar();

	RegisterToolBarOption();
}

void UDevFrameworkEdSubsystem::RegisterMenuBar()
{
	UToolMenu* MenuBar = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu");

	FToolMenuSection& MenuBarSection = MenuBar->FindOrAddSection(MenuBarSectionName);
	MenuBarSection.AddSubMenu
	(
		"DevFrameworkMenu",
		LOCTEXT("DevFrameworkMenu", "DevFrameworkMenu"),
		LOCTEXT("DevFrameworkMenu_ToolTip", "Open the DevFramework menu"),
		FNewToolMenuDelegate::CreateUObject(this, &UDevFrameworkEdSubsystem::RegisterMenu)
	);

	OnMenuBarExtend.Broadcast(MenuBar);
}

void UDevFrameworkEdSubsystem::RegisterMenu(UToolMenu* InToolMenu)
{
	OnMenuExtend.Broadcast(InToolMenu);
}

void UDevFrameworkEdSubsystem::RegisterToolBar()
{
	UToolMenu* ToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
	OnToolBarExtend.Broadcast(ToolBar);

	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	OnToolBarSectionExtend.Broadcast(ToolBarSection);

	for (auto& Block : ToolBarSection.Blocks)
	{
		Block.SetCommandList(CommandList);
	}

	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;
}

void UDevFrameworkEdSubsystem::RegisterToolBarOption()
{
	UToolMenu* ToolBar = UToolMenus::Get()->FindMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	ToolBarSection.AddEntry
	(
		FToolMenuEntry::InitComboButton
		(
			"DevEdToolBarMenu",
			FUIAction(),
			FNewToolMenuDelegate::CreateUObject(this, &UDevFrameworkEdSubsystem::RegisterToolBarOptionMenu),
			LOCTEXT("DevEdToolBarComboButtonLabel", "Dev ToolBar Options"),
			LOCTEXT("DevEdToolBarComboButtonTooltip", "Open Dev ToolBar Options"),
			FSlateIcon(),
			true
		)
	);

	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;
}

void UDevFrameworkEdSubsystem::RegisterToolBarOptionMenu(UToolMenu* InToolMenu)
{
	OnToolBarOptionExtend.Broadcast(InToolMenu);
}

void UDevFrameworkEdSubsystem::RegisterToolBarDeveloperSettingCommand(TSharedPtr<FUICommandList>& InCommandList)
{
	const FDeveloperSettingCommands& Commands = FDeveloperSettingCommands::Get();
	InCommandList->MapAction(Commands.OpenDeveloperSetting, FExecuteAction::CreateUObject(this, &UDevFrameworkEdSubsystem::OpenToolBarManagerSetting));
}

void UDevFrameworkEdSubsystem::RegisterToolBarDeveloperSetting(FToolMenuSection& ToolMenuSection)
{
	ToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			FDeveloperSettingCommands::Get().OpenDeveloperSetting,
			FText::GetEmpty(),
			TAttribute<FText>(),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Manager.ToolbarButton", "Manager.ToolbarButton.Small")
		)
	);
}

void UDevFrameworkEdSubsystem::OpenToolBarManagerSetting()
{
	ISettingsModule& SettingsModule = FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.ShowViewer("Developer", "Global", "Global");
}

#undef LOCTEXT_NAMESPACE
