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
	virtual void InitCommandList(TSharedPtr<FUICommandList>& InCommandList) { return; }

	UFUNCTION(BlueprintNativeEvent, Category="Manager Editor Interface")
	void ExtendMenu(UToolMenu* InToolMenu);

	UFUNCTION(BlueprintNativeEvent, Category="Manager Editor Interface")
	void ExtendToolBar(FToolMenuSection& InSection);

	UFUNCTION(BlueprintNativeEvent, Category="Manager Editor Interface")
	void ExtendToolBarMenu(UToolMenu* InToolMenu);
};
