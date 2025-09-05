// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Interface/ManagerInterface.h"
#include "BlueprintEditorManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBlueprintEditorManager : public UEditorSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UBlueprint* FindOpenedBlueprintByCDO(UObject* InObject);

private:
	TArray<TObjectPtr<UBlueprint>> OpenedBlueprints;

	void OnAssetEditorOpened(UObject* InObject);
	void OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason);
};
