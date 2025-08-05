// Copyright Epic Games, Inc. All Rights Reserved.

#include "Chart3d.h"

#define LOCTEXT_NAMESPACE "FChart3dModule"

void FChart3dModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FChart3dModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChart3dModule, Chart3d)