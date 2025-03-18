// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "DevFrameworkEdSubsystem.generated.h"

class IManagerEdInterface;
class ILevelEditor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandListInitialize, TSharedPtr<FUICommandList>&)
DECLARE_MULTICAST_DELEGATE_OneParam(FToolMenuDelegate, UToolMenu*&)
DECLARE_MULTICAST_DELEGATE_OneParam(FFToolMenuSectionDelegate, FToolMenuSection&)

struct FDevFrameworkDelegate
{
public:
	DEVEDCORE_API static FOnCommandListInitialize OnCommandListInitialize;

	DEVEDCORE_API static FToolMenuDelegate OnMenuBarExtend;
	DEVEDCORE_API static FToolMenuDelegate OnMenuExtend;

	DEVEDCORE_API static FToolMenuDelegate OnToolBarExtend;
	DEVEDCORE_API static FFToolMenuSectionDelegate OnToolBarSectionExtend;
	DEVEDCORE_API static FToolMenuDelegate OnToolBarOptionExtend;
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UDevFrameworkEdSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	static UDevFrameworkEdSubsystem* Get();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	virtual void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	virtual void RegisterMenuBar();
	virtual void RegisterMenu(UToolMenu* InToolMenu);
	virtual void RegisterToolBar();
	virtual void RegisterToolBarOption();
	virtual void RegisterToolBarOptionMenu(UToolMenu* InToolMenu);

protected:
	static FName MenuBarSectionName;
	static FName ToolBarSectionName;
	TSharedPtr<FUICommandList> CommandList = nullptr;
};
