// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Subsystem/GenericFrameworkEdSubsystem.h"

#include "LevelEditor.h"

FOnCommandListInitialize UGenericFrameworkEdSubsystem::OnCommandListInitialize;
FToolMenuDelegate UGenericFrameworkEdSubsystem::OnMenuBarExtend;
FToolMenuDelegate UGenericFrameworkEdSubsystem::OnMenuExtend;
FToolMenuDelegate UGenericFrameworkEdSubsystem::OnToolBarExtend;
FFToolMenuSectionDelegate UGenericFrameworkEdSubsystem::OnToolBarSectionExtend;
FToolMenuDelegate UGenericFrameworkEdSubsystem::OnToolBarOptionExtend;

FName UGenericFrameworkEdSubsystem::MenuBarSectionName = "GenericFrameworkMenuBar";
FName UGenericFrameworkEdSubsystem::ToolBarSectionName = "GenericFrameworkTooBar";

UGenericFrameworkEdSubsystem* UGenericFrameworkEdSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UGenericFrameworkEdSubsystem>();
}

void UGenericFrameworkEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UGenericFrameworkEdSubsystem::OnLevelEditorCreated);
}

void UGenericFrameworkEdSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().RemoveAll(this);
}

void UGenericFrameworkEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	CommandList = MakeShareable(new FUICommandList);
	OnCommandListInitialize.Broadcast(CommandList);

	RegisterMenuBar();

	RegisterToolBar();

	RegisterToolBarOption();
}

void UGenericFrameworkEdSubsystem::RegisterMenuBar()
{
	UToolMenu* MenuBar = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu");

	FToolMenuSection& MenuBarSection = MenuBar->FindOrAddSection(MenuBarSectionName);
	MenuBarSection.AddSubMenu
	(
		"GenericFrameworkMenuBar",
		NSLOCTEXT("FDevEdCoreModule", "MenuBarLabel", "Generic Framework"),
		NSLOCTEXT("FDevEdCoreModule", "MenuBarToolTip", "Open the Generic Framework menu"),
		FNewToolMenuDelegate::CreateUObject(this, &UGenericFrameworkEdSubsystem::RegisterMenu)
	);

	OnMenuBarExtend.Broadcast(MenuBar);
}

void UGenericFrameworkEdSubsystem::RegisterMenu(UToolMenu* InToolMenu)
{
	OnMenuExtend.Broadcast(InToolMenu);
}

void UGenericFrameworkEdSubsystem::RegisterToolBar()
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

void UGenericFrameworkEdSubsystem::RegisterToolBarOption()
{
	UToolMenu* ToolBar = UToolMenus::Get()->FindMenu("LevelEditor.LevelEditorToolBar.User");
	FToolMenuSection& ToolBarSection = ToolBar->FindOrAddSection(ToolBarSectionName);
	ToolBarSection.AddEntry
	(
		FToolMenuEntry::InitComboButton
		(
			"GenericFrameworkToolBar",
			FUIAction(),
			FNewToolMenuDelegate::CreateUObject(this, &UGenericFrameworkEdSubsystem::RegisterToolBarOptionMenu),
			NSLOCTEXT("FDevEdCoreModule", "GenericFrameworkToolBarLabel", "ToolBar Options"),
			NSLOCTEXT("FDevEdCoreModule", "GenericFrameworkToolBarTooltip", "Open ToolBar Options"),
			FSlateIcon(),
			true
		)
	);

	UToolMenu* AssetToolbar = UToolMenus::Get()->ExtendMenu("AssetEditor.DefaultToolBar");
	FToolMenuSection& AssetToolbarSection = AssetToolbar->FindOrAddSection(ToolBarSectionName);
	AssetToolbarSection = ToolBarSection;
}

void UGenericFrameworkEdSubsystem::RegisterToolBarOptionMenu(UToolMenu* InToolMenu)
{
	if (!InToolMenu->FindSection("Tools"))
	{
		InToolMenu->AddSection(FName("Tools"),NSLOCTEXT("FDevEdCoreModule", "ToolsSectionLabel", "Tools"));
	}

	OnToolBarOptionExtend.Broadcast(InToolMenu);
}
