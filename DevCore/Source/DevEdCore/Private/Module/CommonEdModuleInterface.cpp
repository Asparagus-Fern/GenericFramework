// Fill out your copyright notice in the Description page of Project Settings.

#include "Module/CommonEdModuleInterface.h"

#include "AssetToolsModule.h"
#include "Factory/AssetTypeActions.h"

#define LOCTEXT_NAMESPACE "ICommonEdModuleInterface"

void ICommonEdModuleInterface::StartupModule()
{
	ICommonModuleInterface::StartupModule();

	RegisterStyle();
	RegisterCommand();
	
	IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
	AssetCategory = AssetTools.FindAdvancedAssetCategory("DevFramework");
	RegisterAssetActions(AssetActions);
	for (auto& RegisterAssetActions : AssetActions)
	{
		AssetTools.RegisterAssetTypeActions(RegisterAssetActions.ToSharedRef());
	}
}

void ICommonEdModuleInterface::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("DevEdCore");
}

void ICommonEdModuleInterface::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();

	FModuleStatus OutModuleStatus;
	if (FModuleManager::Get().QueryModule("AssetTools", OutModuleStatus))
	{
		if (OutModuleStatus.bIsLoaded)
		{
			IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
			for (auto UnRegisterAssetActions : AssetActions)
			{
				AssetTools.UnregisterAssetTypeActions(UnRegisterAssetActions.ToSharedRef());
			}
		}
	}

	UnRegisterCommand();
	UnRegisterStyle();
}

#undef LOCTEXT_NAMESPACE
