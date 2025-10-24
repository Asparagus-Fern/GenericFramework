// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPIModule.h"
#include "INativeAPISessionFeature.h"
#include "Session/NativeAPISession_WebSocket.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "FNativeAPIModule"

void FNativeAPIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IModularFeatures::Get().RegisterModularFeature(INativeAPISessionFeature::GetFeatureName(), new FNativeAPISession_WebSocket);
}

void FNativeAPIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNativeAPIModule, NativeAPI)
