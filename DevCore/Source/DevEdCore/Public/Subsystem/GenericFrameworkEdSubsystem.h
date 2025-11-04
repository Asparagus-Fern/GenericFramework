// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "GenericFrameworkEdSubsystem.generated.h"

class IManagerEdInterface;
class ILevelEditor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandListInitialize, TSharedPtr<FUICommandList>&)
DECLARE_MULTICAST_DELEGATE_OneParam(FToolMenuDelegate, UToolMenu*&)
DECLARE_MULTICAST_DELEGATE_OneParam(FFToolMenuSectionDelegate, FToolMenuSection&)

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericFrameworkEdSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	static UGenericFrameworkEdSubsystem* Get();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);
	void RegisterMenuBar();
	void RegisterMenu(UToolMenu* InToolMenu);
	void RegisterToolBar();
	void RegisterToolBarOption();
	void RegisterToolBarOptionMenu(UToolMenu* InToolMenu);

public:
	DEVEDCORE_API static FOnCommandListInitialize OnCommandListInitialize;
	DEVEDCORE_API static FToolMenuDelegate OnMenuBarExtend;
	DEVEDCORE_API static FToolMenuDelegate OnMenuExtend;
	DEVEDCORE_API static FToolMenuDelegate OnToolBarExtend;
	DEVEDCORE_API static FFToolMenuSectionDelegate OnToolBarSectionExtend;
	DEVEDCORE_API static FToolMenuDelegate OnToolBarOptionExtend;

protected:
	static FName MenuBarSectionName;
	static FName ToolBarSectionName;
	TSharedPtr<FUICommandList> CommandList = nullptr;
};
