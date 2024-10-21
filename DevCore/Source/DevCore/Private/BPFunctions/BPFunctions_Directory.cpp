// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Directory.h"

#include "Interfaces/IPluginManager.h"

bool UBPFunctions_Directory::GetPluginBaseDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir();
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginBinariesDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Binaries";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginContentDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetContentDir();
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginIntermediateDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Intermediate";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginResourcesDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Resources";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginSourceDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Source";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginExtraDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Extra";
		return true;
	}
	return false;
}
