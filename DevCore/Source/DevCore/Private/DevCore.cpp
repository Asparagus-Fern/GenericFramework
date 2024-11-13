// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevCore.h"

#define LOCTEXT_NAMESPACE "FDevCoreModule"

void FDevCoreModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FDevCoreModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevCoreModule, DevCore)
