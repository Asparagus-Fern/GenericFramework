// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Manager/CoreInternalManager.h"
#include "BlueprintEditorNodeSpawnerManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBlueprintEditorNodeSpawnerManager : public UEditorSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UBlueprint* FindOpenedBlueprintByCDO(UObject* InObject);

private:
	TArray<TObjectPtr<UBlueprint>> OpenedBlueprints;

	void OnAssetEditorOpened(UObject* InObject);
	void OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason);
};
