// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "DevFrameworkEdSubsystem.generated.h"

class IManagerEdInterface;
class ILevelEditor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandListInitialize, TSharedPtr<FUICommandList>&)
DECLARE_MULTICAST_DELEGATE_OneParam(FToolMenuDelegate, UToolMenu*)
DECLARE_MULTICAST_DELEGATE_OneParam(FFToolMenuSectionDelegate, FToolMenuSection&)

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

public:
	inline static FOnCommandListInitialize OnCommandListInitialize;

	inline static FToolMenuDelegate OnMenuBarExtend;
	inline static FToolMenuDelegate OnMenuExtend;

	inline static FToolMenuDelegate OnToolBarExtend;
	inline static FFToolMenuSectionDelegate OnToolBarSectionExtend;
	inline static FToolMenuDelegate OnToolBarOptionExtend;

private:
	virtual void RegisterToolBarDeveloperSettingCommand(TSharedPtr<FUICommandList>& InCommandList);
	virtual void RegisterToolBarDeveloperSetting(FToolMenuSection& ToolMenuSection);
	virtual void OpenToolBarManagerSetting();
};
