// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/BlueprintEditorManager.h"

void UBlueprintEditorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UBlueprintEditorManager::OnAssetEditorOpened);
	AssetEditorSubsystem->OnAssetEditorRequestClose().AddUObject(this, &UBlueprintEditorManager::OnAssetEditorRequestClose);
}

void UBlueprintEditorManager::Deinitialize()
{
	Super::Deinitialize();

	if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
	{
		AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
		AssetEditorSubsystem->OnAssetEditorRequestClose().RemoveAll(this);
	}

	UnRegisterManager();
}

UBlueprint* UBlueprintEditorManager::FindOpenedBlueprintByCDO(UObject* InObject)
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

void UBlueprintEditorManager::OnAssetEditorOpened(UObject* InObject)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && !OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Add(Blueprint);
	}
}

void UBlueprintEditorManager::OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Remove(Blueprint);
	}
}
