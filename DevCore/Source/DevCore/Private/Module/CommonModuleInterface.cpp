// Fill out your copyright notice in the Description page of Project Settings.

#include "Module/CommonModuleInterface.h"

#include "Manager/ManagerSubsystem.h"
#include "Manager/ManagerType.h"

void ICommonModuleInterface::StartupModule()
{
	PostStartupModule();
	LoadDependentModule_Internal();
	RegisterManagers_Internal();
}

void ICommonModuleInterface::ShutdownModule()
{
	PreShutdownModule();
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

void ICommonModuleInterface::RegisterManagers_Internal()
{
	if (!UManagerSubsystem::bManagerSubsystemInitialize)
	{
		ManagerSubsystemInitializeHandle = FManagerDelegates::OnManagerSubsystemInitialize.AddRaw(this, &ICommonModuleInterface::OnManagerSubsystemInitialize);
	}
	else
	{
		TArray<TSubclassOf<UCoreManager>> ManagerClasses;
		GetRegisterManager(ManagerClasses);
		for (const auto& ManagerClass : ManagerClasses)
		{
			GEngine->GetEngineSubsystem<UManagerSubsystem>()->RegisterManager(ManagerClass);
		}
	}
}

void ICommonModuleInterface::OnManagerSubsystemInitialize()
{
	FManagerDelegates::OnManagerSubsystemInitialize.Remove(ManagerSubsystemInitializeHandle);

	TArray<TSubclassOf<UCoreManager>> ManagerClasses;
	GetRegisterManager(ManagerClasses);
	for (const auto& ManagerClass : ManagerClasses)
	{
		UManagerSubsystem::Get()->RegisterManager(ManagerClass);
	}
}

void ICommonModuleInterface::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	InDependentModuleName.Add("DevCore");
}

void ICommonModuleInterface::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
}
