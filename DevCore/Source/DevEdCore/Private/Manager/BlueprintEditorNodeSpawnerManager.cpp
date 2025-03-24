// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/BlueprintEditorNodeSpawnerManager.h"

void UBlueprintEditorNodeSpawnerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UBlueprintEditorNodeSpawnerManager::OnAssetEditorOpened);
	AssetEditorSubsystem->OnAssetEditorRequestClose().AddUObject(this, &UBlueprintEditorNodeSpawnerManager::OnAssetEditorRequestClose);
}

void UBlueprintEditorNodeSpawnerManager::Deinitialize()
{
	Super::Deinitialize();

	if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
	{
		AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
		AssetEditorSubsystem->OnAssetEditorRequestClose().RemoveAll(this);
	}

	UnRegisterManager();
}

UBlueprint* UBlueprintEditorNodeSpawnerManager::FindOpenedBlueprintByCDO(UObject* InObject)
{
	for (const auto& OpenedBlueprint : OpenedBlueprints)
	{
		if (OpenedBlueprint->GeneratedClass->ClassDefaultObject == InObject)
		{
			return OpenedBlueprint;
		}
	}

	return nullptr;
}

void UBlueprintEditorNodeSpawnerManager::OnAssetEditorOpened(UObject* InObject)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && !OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Add(Blueprint);
	}

	// if (Blueprint->GeneratedClass->IsChildOf(UMenuCollection::StaticClass()))
	// {
	// 	const TSharedPtr<FBlueprintEditor> BlueprintEditor = UBPFunctions_BlueprintEditor::GetBlueprintEditor(Blueprint);
	// 	if (BlueprintEditor.IsValid())
	// 	{
	// 		if (!BlueprintEditor->GetTabManager()->FindExistingLiveTab(MenuCollectionHierarchyTabID).IsValid())
	// 		{
	// 			BlueprintEditor->GetTabManager()->TryInvokeTab(MenuCollectionHierarchyTabID);
	// 		}
	// 	}
	// }
}

void UBlueprintEditorNodeSpawnerManager::OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Remove(Blueprint);
	}
}
