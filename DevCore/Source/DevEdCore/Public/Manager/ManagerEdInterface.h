// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToolMenuSection.h"
#include "Manager/ManagerInterface.h"
#include "ManagerEdInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class UManagerEdInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVEDCORE_API IManagerEdInterface
{
	GENERATED_BODY()

public:
	IManagerEdInterface();

public:
	UFUNCTION(BlueprintNativeEvent, Category="Editor Manager Interface")
	void OnEditorActived();
	virtual void NativeOnEditorActived();

	UFUNCTION(BlueprintNativeEvent, Category="Editor Manager Interface")
	void OnEditorInactived();
	virtual void NativeOnEditorInactived();

	bool GetIsEditorActived() const { return bEditorActived; }

public:
	virtual void InitCommandList(TSharedPtr<FUICommandList>& InCommandList) { return; }
	virtual void ExtendMenu(UToolMenu* InToolMenu) { return; }
	virtual void ExtendToolBar(FToolMenuSection& InSection) { return; }
	virtual void ExtendToolBarMenu(UToolMenu* InToolMenu) { return; }

protected:
	uint8 bEditorActived : 1;
};
