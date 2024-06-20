// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"

class DEVCORE_API FStaticFunctions_Plugin
{
public:
	static TSharedPtr<IPlugin> FindPlugin(const FString& InPluginName);

	static FString GetPluginBaseDir(const FString& InPluginName);
	static FString GetPluginBinariesDir(const FString& InPluginName);
	static FString GetPluginContentDir(const FString& InPluginName);
	static FString GetPluginIntermediateDir(const FString& InPluginName);
	static FString GetPluginResourcesDir(const FString& InPluginName);
	static FString GetPluginSourceDir(const FString& InPluginName);

	static FString GetPluginExtraDir(const FString& InPluginName);
};
