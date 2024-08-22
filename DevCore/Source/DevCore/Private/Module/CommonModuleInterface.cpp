// Fill out your copyright notice in the Description page of Project Settings.

#include "Module/CommonModuleInterface.h"

void ICommonModuleInterface::StartupModule()
{
	LoadDependentModule_Internal();
}

void ICommonModuleInterface::ShutdownModule()
{
}

void ICommonModuleInterface::LoadDependentModule_Internal()
{
	TArray<FName> DependentModuleName;
	LoadDependentModule(DependentModuleName);

	for (const auto ModuleName : DependentModuleName)
	{
		FModuleManager::Get().LoadModuleChecked(ModuleName);
	}
}

void ICommonModuleInterface::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	InDependentModuleName.Add("DevSlateCore");
	InDependentModuleName.Add("DevCore");
}
