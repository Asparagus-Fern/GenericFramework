// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "DocumentSubsystem.generated.h"

class ISettingsEditorModel;

static const FName DocumentTabName("DeveloperDocument");

/**
 * 
 */
UCLASS()
class DOCUMENTREADER_API UDocumentSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	void OnToolBarSectionExtend(FToolMenuSection& InToolMenuSection);
	void OpenDucument();
	TSharedRef<SDockTab> HandleSpawnDocumentTab(const FSpawnTabArgs& SpawnTabArgs);
};
