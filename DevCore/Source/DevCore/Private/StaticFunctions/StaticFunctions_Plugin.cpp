// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticFunctions/StaticFunctions_Plugin.h"

#include "StaticFunctions/StaticFunctions_Folder.h"

TSharedPtr<IPlugin> FStaticFunctions_Plugin::FindPlugin(const FString& InPluginName)
{
	return IPluginManager::Get().FindPlugin(InPluginName);
}

FString FStaticFunctions_Plugin::GetPluginBaseDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetBaseDir();
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginBinariesDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetBaseDir() + "/Binaries";
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginContentDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetContentDir();
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginIntermediateDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetBaseDir() + "/Intermediate";
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginResourcesDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetBaseDir() + "/Resources";
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginSourceDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		return FindPlugin(InPluginName)->GetBaseDir() + "/Source";
	}
	return {};
}

FString FStaticFunctions_Plugin::GetPluginExtraDir(const FString& InPluginName)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		FString ExtraPath = FindPlugin(InPluginName)->GetBaseDir() + "/Extra";
		if (!FStaticFunctions_Folder::ExistFolder(*ExtraPath))
		{
			FStaticFunctions_Folder::CreateFolder(*ExtraPath);
		}
		return ExtraPath;
	}
	return {};
}
