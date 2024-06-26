// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerEdSubsystem.h"

#include "DevEdCoreStyle.h"
#include "LevelEditor.h"
#include "Manager/ManagerEdInterface.h"
#include "Manager/ManagerGlobal.h"

#define LOCTEXT_NAMESPACE "UManagerEdSubsystem"

bool UManagerEdSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UManagerEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UManagerEdSubsystem::OnLevelEditorCreated);

	FWorldDelegates::OnPIEStarted.AddUObject(this, &UManagerEdSubsystem::OnPIEStarted);
	FWorldDelegates::OnPIEEnded.AddUObject(this, &UManagerEdSubsystem::OnPIEEnded);
}

void UManagerEdSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UManagerEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	ExtendEditor();
}

void UManagerEdSubsystem::OnPIEStarted(UGameInstance* InGameInstance)
{
	if (true)
	{
	}
}

void UManagerEdSubsystem::OnPIEEnded(UGameInstance* InGameInstance)
{
	if (true)
	{
	}
}

void UManagerEdSubsystem::ExtendEditor()
{
	CommandList = MakeShareable(new FUICommandList);

	/* 扩展 ToolBar */
	UToolMenu* ToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);

	/* IManagerEdInterface 扩展 ToolBar 接口 */
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>())
	{
		Interface->InitCommandList(CommandList);
		Interface->ExtendToolBar(ToolBarSection);
	}

	for (auto& Block : ToolBarSection.Blocks)
	{
		Block.SetCommandList(CommandList);
	}

	/* 同步到 Asset Editor ToolBar */
	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;

	RegisterEditorMenuBar();
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
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>())
	{
		Interface->ExtendMenu(InToolMenu);
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
	for (const auto& Interface : GetManagersWithInterface<IManagerEdInterface>())
	{
		Interface->ExtendToolBarMenu(InToolMenu);
	}
}

#undef LOCTEXT_NAMESPACE
