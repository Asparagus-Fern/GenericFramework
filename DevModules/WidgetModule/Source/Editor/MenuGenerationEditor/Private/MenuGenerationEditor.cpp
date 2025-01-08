#include "MenuGenerationEditor.h"

#include "BlueprintEditorModule.h"
#include "SMenuCollectionHierarchy.h"
#include "BPFunctions/BPFunctions_BlueprintEditor.h"
#include "Entity/MenuCollection.h"
#include "Framework/Docking/LayoutExtender.h"

#define LOCTEXT_NAMESPACE "FMenuGenerationEditorModule"

void FMenuGenerationEditorModule::StartupModule()
{
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	BlueprintEditorTabSpawnerHandle = BlueprintEditorModule.OnRegisterTabsForEditor().AddRaw(this, &FMenuGenerationEditorModule::RegisterBlueprintEditorTab);
	BlueprintEditorLayoutExtensionHandle = BlueprintEditorModule.OnRegisterLayoutExtensions().AddRaw(this, &FMenuGenerationEditorModule::RegisterBlueprintEditorLayout);

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	AssetEditorOpenedHandle = AssetEditorSubsystem->OnAssetEditorOpened().AddRaw(this, &FMenuGenerationEditorModule::OnAssetEditorOpened);
}

void FMenuGenerationEditorModule::ShutdownModule()
{
	if (FBlueprintEditorModule* BlueprintEditorModule = FModuleManager::GetModulePtr<FBlueprintEditorModule>("Kismet"))
	{
		BlueprintEditorModule->OnRegisterTabsForEditor().Remove(BlueprintEditorTabSpawnerHandle);
		BlueprintEditorModule->OnRegisterLayoutExtensions().Remove(BlueprintEditorLayoutExtensionHandle);
	}
}

void FMenuGenerationEditorModule::RegisterBlueprintEditorTab(FWorkflowAllowedTabSet& TabFactories, FName InModeName, TSharedPtr<FBlueprintEditor> BlueprintEditor)
{
	if (BlueprintEditor->GetBlueprintObj()->GeneratedClass->IsChildOf(UMenuCollection::StaticClass()))
	{
		TabFactories.RegisterFactory(MakeShared<FMenuCollectionEditorSummoner>(BlueprintEditor));
	}
}

void FMenuGenerationEditorModule::RegisterBlueprintEditorLayout(FLayoutExtender& Extender)
{
	Extender.ExtendLayout(FTabId("ContentBrowserTab1"), ELayoutExtensionPosition::Before, FTabManager::FTab(MenuCollectionHierarchyTabID, ETabState::OpenedTab));
}

void FMenuGenerationEditorModule::OnAssetEditorOpened(UObject* InObject)
{
	if (const UBlueprint* Blueprint = Cast<UBlueprint>(InObject))
	{
		if (Blueprint->GeneratedClass->IsChildOf(UMenuCollection::StaticClass()))
		{
			const TSharedPtr<FBlueprintEditor> BlueprintEditor = UBPFunctions_BlueprintEditor::GetBlueprintEditor(Blueprint);
			if (BlueprintEditor.IsValid())
			{
				if (!BlueprintEditor->GetTabManager()->FindExistingLiveTab(MenuCollectionHierarchyTabID).IsValid())
				{
					BlueprintEditor->GetTabManager()->TryInvokeTab(MenuCollectionHierarchyTabID);
				}
			}
		}
	}
}

FMenuCollectionEditorSummoner::FMenuCollectionEditorSummoner(TSharedPtr<FBlueprintEditor> BlueprintEditor)
	: FWorkflowTabFactory(MenuCollectionHierarchyTabID, BlueprintEditor)
	  , WeakBlueprintEditor(BlueprintEditor)
{
	bIsSingleton = true;
	TabLabel = LOCTEXT("MenuCollectionHierarchyTabName", "Hierarchy");
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ContentBrowser.ShowSourcesView");
}

TSharedRef<SWidget> FMenuCollectionEditorSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return SNew(SMenuCollectionHierarchy, WeakBlueprintEditor);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMenuGenerationEditorModule, MenuGenerationEditor)
