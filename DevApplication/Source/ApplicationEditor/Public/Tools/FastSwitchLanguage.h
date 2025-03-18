// Copyright Chen 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "FastSwitchLanguage.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONEDITOR_API UFastSwitchLanguage : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	void OnToolBarSectionExtend(FToolMenuSection& InToolMenuSection);
	void ToggleSwitchLanguage();
	void RefreshBlueprints();
};
