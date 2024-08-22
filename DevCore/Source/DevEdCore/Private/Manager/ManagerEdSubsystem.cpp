// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerEdSubsystem.h"

#include "LevelEditor.h"
#include "Manager/ManagerEdInterface.h"
#include "Manager/ManagerGlobal.h"

#define LOCTEXT_NAMESPACE "UManagerEdSubsystem"

FName UManagerEdSubsystem::MenuBarSectionName = "DevEdMenuBar";
FName UManagerEdSubsystem::ToolBarSectionName = "DevEdTooBar";

void UManagerEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UManagerEdSubsystem::OnLevelEditorCreated);
}

UManagerEdSubsystem* UManagerEdSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UManagerEdSubsystem>();
}

void UManagerEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	// ExtendEditor();
}

void UManagerEdSubsystem::ExtendEditor()
{
	CommandList = MakeShareable(new FUICommandList);

	/* 扩展 ToolBar */
	UToolMenu* ToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	
	/* IManagerEdInterface 扩展 ToolBar 接口 */
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>(this))
	{
		Interface->InitCommandList(CommandList);
		IManagerEdInterface::Execute_ExtendToolBar(Cast<UCoreManager>(Interface), ToolBarSection);
	}

	for (auto& Block : ToolBarSection.Blocks)
	{
		Block.SetCommandList(CommandList);
	}

	/* 同步到 Asset Editor ToolBar */
	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;
	
	/* 扩展MenuBar */
	RegisterEditorMenuBar();

	/* 扩展ToolBar */
	RegisterEditorToolBarOption();
}

void UManagerEdSubsystem::RegisterEditorMenuBar()
{
	/* 扩展 MenuBar*/
	UToolMenu* MenuBar = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu");
	FToolMenuSection& MenuBarSection = MenuBar->FindOrAddSection(MenuBarSectionName);

	MenuBarSection.AddSubMenu
	(
		"DevFrameworkMenu",
		LOCTEXT("DevFrameworkMenu", "DevFrameworkMenu"),
		LOCTEXT("DevFrameworkMenu_ToolTip", "Open the DevFramework menu"),
		FNewToolMenuDelegate::CreateUObject(this, &UManagerEdSubsystem::RegisterEditorMenuBarMenu)
	);
}

void UManagerEdSubsystem::RegisterEditorMenuBarMenu(UToolMenu* InToolMenu)
{
	/* IManagerEdInterface 扩展 MenuBar 接口 */
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>(this))
	{
		IManagerEdInterface::Execute_ExtendMenu(Cast<UCoreManager>(Interface), InToolMenu);
	}
}

void UManagerEdSubsystem::RegisterEditorToolBarOption()
{
	/* 扩展 ToolBar 选项卡 */
	UToolMenu* ToolBar = UToolMenus::Get()->FindMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	ToolBarSection.AddEntry
	(
		FToolMenuEntry::InitComboButton
		(
			"DevEdToolBarMenu",
			FUIAction(),
			FNewToolMenuDelegate::CreateUObject(this, &UManagerEdSubsystem::RegisterEditorToolBarOptionMenu),
			LOCTEXT("DevEdToolBarComboButtonLabel", "Dev ToolBar Options"),
			LOCTEXT("DevEdToolBarComboButtonTooltip", "Open Dev ToolBar Options"),
			FSlateIcon(),
			true
		)
	);

	/* 同步扩展 Asset Editor */
	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;
}

void UManagerEdSubsystem::RegisterEditorToolBarOptionMenu(UToolMenu* InToolMenu)
{
	/* IManagerEdInterface 扩展 ToolBar选项卡 接口 */
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>(this))
	{
		IManagerEdInterface::Execute_ExtendToolBarMenu(Cast<UCoreManager>(Interface), InToolMenu);
	}
}

#undef LOCTEXT_NAMESPACE
