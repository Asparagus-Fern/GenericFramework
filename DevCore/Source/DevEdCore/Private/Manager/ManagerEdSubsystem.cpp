// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerEdSubsystem.h"

#include "DevCoreStyle.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "ManagerSetting/ManagerSettingCommands.h"

#define LOCTEXT_NAMESPACE "UManagerEdSubsystem"

FName UManagerEdSubsystem::MenuBarSectionName = "DevEdMenuBar";
FName UManagerEdSubsystem::ToolBarSectionName = "DevEdTooBar";

UManagerEdSubsystem::FOnCommandListInitialize UManagerEdSubsystem::OnCommandListInitialize;
UManagerEdSubsystem::FToolMenuDelegate UManagerEdSubsystem::OnMenuBarExtend;
UManagerEdSubsystem::FToolMenuDelegate UManagerEdSubsystem::OnMenuExtend;
UManagerEdSubsystem::FToolMenuDelegate UManagerEdSubsystem::OnToolBarExtend;
UManagerEdSubsystem::FFToolMenuSectionDelegate UManagerEdSubsystem::OnToolBarSectionExtend;
UManagerEdSubsystem::FToolMenuDelegate UManagerEdSubsystem::OnToolBarOptionExtend;

void UManagerEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UManagerEdSubsystem::OnLevelEditorCreated);

	OnCommandListInitialize.AddUObject(this, &UManagerEdSubsystem::RegisterToolBarManagerSettingCommand);
	OnToolBarSectionExtend.AddUObject(this, &UManagerEdSubsystem::RegisterToolBarManagerSetting);
}

UManagerEdSubsystem* UManagerEdSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UManagerEdSubsystem>();
}

void UManagerEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	CommandList = MakeShareable(new FUICommandList);
	OnCommandListInitialize.Broadcast(CommandList);

	RegisterMenuBar();

	RegisterToolBar();

	RegisterToolBarOption();
}

void UManagerEdSubsystem::RegisterMenuBar()
{
	UToolMenu* MenuBar = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu");
	OnMenuBarExtend.Broadcast(MenuBar);

	FToolMenuSection& MenuBarSection = MenuBar->FindOrAddSection(MenuBarSectionName);
	MenuBarSection.AddSubMenu
	(
		"DevFrameworkMenu",
		LOCTEXT("DevFrameworkMenu", "DevFrameworkMenu"),
		LOCTEXT("DevFrameworkMenu_ToolTip", "Open the DevFramework menu"),
		FNewToolMenuDelegate::CreateUObject(this, &UManagerEdSubsystem::RegisterMenu)
	);
}

void UManagerEdSubsystem::RegisterMenu(UToolMenu* InToolMenu)
{
	OnMenuExtend.Broadcast(InToolMenu);
}

void UManagerEdSubsystem::RegisterToolBar()
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

void UManagerEdSubsystem::RegisterToolBarOption()
{
	UToolMenu* ToolBar = UToolMenus::Get()->FindMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	ToolBarSection.AddEntry
	(
		FToolMenuEntry::InitComboButton
		(
			"DevEdToolBarMenu",
			FUIAction(),
			FNewToolMenuDelegate::CreateUObject(this, &UManagerEdSubsystem::RegisterToolBarOptionMenu),
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

void UManagerEdSubsystem::RegisterToolBarOptionMenu(UToolMenu* InToolMenu)
{
	OnToolBarOptionExtend.Broadcast(InToolMenu);
}

void UManagerEdSubsystem::RegisterToolBarManagerSettingCommand(TSharedPtr<FUICommandList>& InCommandList)
{
	const FManagerSettingCommands& Commands = FManagerSettingCommands::Get();
	InCommandList->MapAction(Commands.OpenManagerSetting, FExecuteAction::CreateUObject(this, &UManagerEdSubsystem::OpenToolBarManagerSetting));
}

void UManagerEdSubsystem::RegisterToolBarManagerSetting(FToolMenuSection& ToolMenuSection)
{
	ToolMenuSection.AddEntry
	(
		FToolMenuEntry::InitToolBarButton
		(
			FManagerSettingCommands::Get().OpenManagerSetting,
			FText::GetEmpty(),
			TAttribute<FText>(),
			FSlateIcon(FDevCoreStyle::GetStyleSetName(), "Manager.ToolbarButton", "Manager.ToolbarButton.Small")
		)
	);
}

void UManagerEdSubsystem::OpenToolBarManagerSetting()
{
	ISettingsModule& SettingsModule = FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.ShowViewer("Manager", "Manager(Global)", "Global");
}

#undef LOCTEXT_NAMESPACE
