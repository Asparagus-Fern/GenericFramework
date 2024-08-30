// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "ManagerEdSubsystem.generated.h"

class IManagerEdInterface;
class ILevelEditor;

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UManagerEdSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	static UManagerEdSubsystem* Get();

protected:
	FDelegateHandle LevelEditorCreatedHandle;
	virtual void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

protected:
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
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCommandListInitialize, TSharedPtr<FUICommandList>&)
	static FOnCommandListInitialize OnCommandListInitialize;

	DECLARE_MULTICAST_DELEGATE_OneParam(FToolMenuDelegate, UToolMenu*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FFToolMenuSectionDelegate, FToolMenuSection&)

	static FToolMenuDelegate OnMenuBarExtend;
	static FToolMenuDelegate OnMenuExtend;

	static FToolMenuDelegate OnToolBarExtend;
	static FFToolMenuSectionDelegate OnToolBarSectionExtend;
	static FToolMenuDelegate OnToolBarOptionExtend;

protected:
	virtual void RegisterToolBarManagerSettingCommand(TSharedPtr<FUICommandList>& InCommandList);
	virtual void RegisterToolBarManagerSetting(FToolMenuSection& ToolMenuSection);
	virtual void OpenToolBarManagerSetting();
};
