// Copyright ChenTaiye 2025. All Rights Reserved.


#include "DevFrameworkEdSubsystem.h"

#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "UManagerEdSubsystem"

FOnCommandListInitialize FDevFrameworkDelegate::OnCommandListInitialize;
FToolMenuDelegate FDevFrameworkDelegate::OnMenuBarExtend;
FToolMenuDelegate FDevFrameworkDelegate::OnMenuExtend;
FToolMenuDelegate FDevFrameworkDelegate::OnToolBarExtend;
FFToolMenuSectionDelegate FDevFrameworkDelegate::OnToolBarSectionExtend;
FToolMenuDelegate FDevFrameworkDelegate::OnToolBarOptionExtend;

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
}

void UDevFrameworkEdSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().RemoveAll(this);
}

void UDevFrameworkEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	CommandList = MakeShareable(new FUICommandList);
	FDevFrameworkDelegate::OnCommandListInitialize.Broadcast(CommandList);

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

	FDevFrameworkDelegate::OnMenuBarExtend.Broadcast(MenuBar);
}

void UDevFrameworkEdSubsystem::RegisterMenu(UToolMenu* InToolMenu)
{
	FDevFrameworkDelegate::OnMenuExtend.Broadcast(InToolMenu);
}

void UDevFrameworkEdSubsystem::RegisterToolBar()
{
	UToolMenu* ToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");
	FDevFrameworkDelegate::OnToolBarExtend.Broadcast(ToolBar);

	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	FDevFrameworkDelegate::OnToolBarSectionExtend.Broadcast(ToolBarSection);

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
	if (!InToolMenu->FindSection("Tools"))
	{
		InToolMenu->AddSection(FName("Tools"),LOCTEXT("ToolsSectionLabel", "Tools"));
	}

	FDevFrameworkDelegate::OnToolBarOptionExtend.Broadcast(InToolMenu);
}

#undef LOCTEXT_NAMESPACE
