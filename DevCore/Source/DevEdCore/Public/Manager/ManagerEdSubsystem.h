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
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle PIEBeginHandle;
	void OnPIEBegin(const bool bIsSimulating);

	FDelegateHandle PIEEndHandle;
	void OnPIEEnd(const bool bIsSimulating);
	
protected:
	virtual void ExtendEditor();
	virtual void RegisterEditorMenuBar();
	virtual void RegisterEditorMenuBarMenu(UToolMenu* InToolMenu);
	virtual void RegisterEditorToolBarOption();
	virtual void RegisterEditorToolBarOptionMenu(UToolMenu* InToolMenu);

protected:
	FName MenuBarSectionName = "DevEdMenuBar";
	FName ToolBarSectionName = "DevEdTooBar";
	TSharedPtr<FUICommandList> CommandList = nullptr;
};
