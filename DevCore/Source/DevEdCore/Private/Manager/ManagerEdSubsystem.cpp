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
	MapChangedHandle = LevelEditorModule.OnMapChanged().AddUObject(this, &UManagerEdSubsystem::OnMapChanged);

	PIEBeginHandle = FEditorDelegates::BeginPIE.AddUObject(this, &UManagerEdSubsystem::OnPIEBegin);
	PIEEndHandle = FEditorDelegates::EndPIE.AddUObject(this, &UManagerEdSubsystem::OnPIEEnd);

	EditorCloseHandle = GEditor->OnEditorClose().AddUObject(this, &UManagerEdSubsystem::OnEditorClose);
}

void UManagerEdSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UManagerEdSubsystem* UManagerEdSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UManagerEdSubsystem>();
}

UWorld* UManagerEdSubsystem::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("Manager: %s has a null OuterPrivate in UCoreManager::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return EditorWorld;
	}
	return Super::GetWorld();
}

void UManagerEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	ExtendEditor();
}

void UManagerEdSubsystem::OnMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType)
{
	if (InWorld->WorldType == EWorldType::Editor || InWorld->WorldType == EWorldType::EditorPreview)
	{
		if (InMapChangeType == EMapChangeType::LoadMap || InMapChangeType == EMapChangeType::NewMap)
		{
			EditorWorld = InWorld;

			ProcessManagerInterfacesInOrder<IManagerEdInterface>
			(
				true, [this](IManagerEdInterface* Interface)
				{
					if (!Interface->GetIsEditorActived())
					{
						Interface->NativeOnEditorActived();
					}
				}
			);
		}
		else if (InMapChangeType == EMapChangeType::TearDownWorld)
		{
			ProcessManagerInterfacesInOrder<IManagerEdInterface>
			(
				false, [this](IManagerEdInterface* Interface)
				{
					if (Interface->GetIsEditorActived())
					{
						Interface->NativeOnEditorInactived();
					}
				}
			);

			EditorWorld = nullptr;
		}
	}
}

void UManagerEdSubsystem::OnPIEBegin(const bool bIsSimulating)
{
	ProcessManagerInterfacesInOrder<IManagerEdInterface>
	(
		false, [this](IManagerEdInterface* Interface)
		{
			if (Interface->GetIsEditorActived())
			{
				Interface->NativeOnEditorInactived();
			}
		}
	);
}

void UManagerEdSubsystem::OnPIEEnd(const bool bIsSimulating)
{
	PostManagerInActivedHandle = FManagerDelegates::PostManagerInActived.AddUObject(this, &UManagerEdSubsystem::PostManagerInActived);
}

void UManagerEdSubsystem::PostManagerInActived()
{
	FManagerDelegates::PostManagerInActived.Remove(PostManagerInActivedHandle);

	ProcessManagerInterfacesInOrder<IManagerEdInterface>
	(
		true, [this](IManagerEdInterface* Interface)
		{
			if (!Interface->GetIsEditorActived())
			{
				Interface->NativeOnEditorActived();
			}
		}
	);
}

void UManagerEdSubsystem::OnEditorClose()
{
	ProcessManagerInterfacesInOrder<IManagerEdInterface>
	(
		false, [this](IManagerEdInterface* Interface)
		{
			if (Interface->GetIsEditorActived())
			{
				Interface->NativeOnEditorInactived();
			}
		}
	);

	EditorWorld = nullptr;
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
