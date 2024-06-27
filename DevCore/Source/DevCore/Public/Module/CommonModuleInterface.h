// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UCoreManager;
/**
 * 
 */
class DEVCORE_API ICommonModuleInterface : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override { return true; }

private:
	void LoadDependentModule_Internal();
	void RegisterManagers_Internal();

protected:
	FDelegateHandle ManagerSubsystemInitializeHandle;
	void OnManagerSubsystemInitialize();

protected:
	virtual void PostStartupModule() { return; }
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName);
	virtual void GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses);
	virtual void PreShutdownModule() { return; }
};
