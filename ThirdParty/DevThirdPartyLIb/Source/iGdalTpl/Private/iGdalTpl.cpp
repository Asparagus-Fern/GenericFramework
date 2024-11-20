#include "iGdalTpl.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FiGdalTplModule"

void FiGdalTplModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("iAnalyseThirdPartyLib")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString GeosLibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/gdal/lib/geos.dll"));
	FString Geos_C_LibraryPath = FPaths::Combine(*BaseDir,TEXT("Source/ThirdParty/gdal/lib/geos_c.dll"));
	FString Proj_LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/gdal/lib/proj_9_2.dll"));
	FString Tiff_LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/gdal/lib/tiff.dll"));
	
	FString Gdal_LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/gdal/bin/gdal.dll"));
    
	Geos_LibraryHandle = FPlatformProcess::GetDllHandle(*GeosLibraryPath);
	Geos_C_LibraryHandle = FPlatformProcess::GetDllHandle(*Geos_C_LibraryPath);
	Proj_LibraryHandle = FPlatformProcess::GetDllHandle(*Tiff_LibraryPath);
	Tiff_LibraryHandle = FPlatformProcess::GetDllHandle(*Proj_LibraryPath);
    
	Gdal_LibraryHandle = FPlatformProcess::GetDllHandle(*Gdal_LibraryPath);
    
	if (!Gdal_LibraryHandle){
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("GDALLibrary", "Failed to load GDAL third party library"));
	}
}

void FiGdalTplModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(Geos_LibraryHandle);
	FPlatformProcess::FreeDllHandle(Geos_C_LibraryHandle);
	FPlatformProcess::FreeDllHandle(Proj_LibraryHandle);
	FPlatformProcess::FreeDllHandle(Tiff_LibraryHandle);
	FPlatformProcess::FreeDllHandle(Gdal_LibraryHandle);
    
	Geos_LibraryHandle = nullptr;
	Geos_C_LibraryHandle = nullptr;
	Proj_LibraryHandle = nullptr;
	Tiff_LibraryHandle = nullptr;
	Gdal_LibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FiGdalTplModule, iGdalTpl)