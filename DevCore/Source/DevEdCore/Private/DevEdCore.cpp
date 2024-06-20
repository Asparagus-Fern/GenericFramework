#include "DevEdCore.h"

#include "AssetToolsModule.h"
#include "DevEdCoreStyle.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

void FDevEdCoreModule::PostStartupModule()
{
	FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory("DevFramework", LOCTEXT("DisplayName", "DevFramework"));
	ICommonEdModuleInterface::PostStartupModule();
}

void FDevEdCoreModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	InDependentModuleName.Add("DevCore");
}

void FDevEdCoreModule::RegisterStyle()
{
	FDevEdCoreStyle::Initialize();
}

void FDevEdCoreModule::UnRegisterStyle()
{
	FDevEdCoreStyle::ShoutDown();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevEdCoreModule, DevEdCore)
