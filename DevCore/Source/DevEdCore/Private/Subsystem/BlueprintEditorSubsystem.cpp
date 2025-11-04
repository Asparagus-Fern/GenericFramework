// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Subsystem/BlueprintEditorSubsystem.h"

UBlueprintEditorSubsystem* UBlueprintEditorSubsystem::Get()
{
	return GEditor->GetEditorSubsystem<UBlueprintEditorSubsystem>();
}

void UBlueprintEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UBlueprintEditorSubsystem::OnAssetEditorOpened);
	AssetEditorSubsystem->OnAssetEditorRequestClose().AddUObject(this, &UBlueprintEditorSubsystem::OnAssetEditorRequestClose);
}

void UBlueprintEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();

	if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
	{
		AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
		AssetEditorSubsystem->OnAssetEditorRequestClose().RemoveAll(this);
	}
}

UBlueprint* UBlueprintEditorSubsystem::FindOpenedBlueprintByCDO(UObject* InObject)
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

void UBlueprintEditorSubsystem::OnAssetEditorOpened(UObject* InObject)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && !OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Add(Blueprint);
	}
}

void UBlueprintEditorSubsystem::OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(InObject);
	if (IsValid(Blueprint) && OpenedBlueprints.Contains(Blueprint))
	{
		OpenedBlueprints.Remove(Blueprint);
	}
}
