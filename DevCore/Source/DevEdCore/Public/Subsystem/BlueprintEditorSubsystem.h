// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericEditorSubsystem.h"
#include "BlueprintEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBlueprintEditorSubsystem : public UGenericEditorSubsystem
{
	GENERATED_BODY()

public:
	static UBlueprintEditorSubsystem* Get();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UBlueprint* FindOpenedBlueprintByCDO(UObject* InObject);

private:
	TArray<TObjectPtr<UBlueprint>> OpenedBlueprints;

	void OnAssetEditorOpened(UObject* InObject);
	void OnAssetEditorRequestClose(UObject* InObject, EAssetEditorCloseReason Reason);
};
