// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Directory.h"

#include "Interfaces/IPluginManager.h"

TSharedPtr<IPlugin> UBPFunctions_Directory::FindPlugin(const FString& InPluginName)
{
	return IPluginManager::Get().FindPlugin(InPluginName);
}

bool UBPFunctions_Directory::GetPluginBaseDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir();
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginBinariesDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir() + "/Binaries";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginContentDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetContentDir();
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginIntermediateDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir() + "/Intermediate";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginResourcesDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir() + "/Resources";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginSourceDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir() + "/Source";
		return true;
	}
	return false;
}

bool UBPFunctions_Directory::GetPluginExtraDir(const FString& InPluginName, FString& Directory)
{
	if (FindPlugin(InPluginName).IsValid())
	{
		Directory = FindPlugin(InPluginName)->GetBaseDir() + "/Extra";
		return true;
	}
	return false;
}


