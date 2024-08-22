// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Module/CommonModuleInterface.h"

class FAssetTypeActions;

/**
 * 
 */
class DEVEDCORE_API ICommonEdModuleInterface : public ICommonModuleInterface
{
	/* ICommonModuleInterface */
protected:
	virtual void StartupModule() override;
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
	virtual void ShutdownModule() override;

	/* ICommonEdModuleInterface */
protected:
	virtual void RegisterStyle() { return; }
	virtual void RegisterCommand() { return; }
	virtual void RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions) { return; }
	virtual void UnRegisterCommand() { return; }
	virtual void UnRegisterStyle() { return; }

	/* IModuleInterface */
protected:
	virtual bool IsGameModule() const override { return false; }

protected:
	EAssetTypeCategories::Type AssetCategory = EAssetTypeCategories::None;
	TArray<TSharedPtr<FAssetTypeActions>> AssetActions;
};
