#include "DevEdCore.h"

#include "AssetToolsModule.h"
#include "Procedure/GameplayProcedureActions.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

void FDevEdCoreModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();
	FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory("DevFramework", LOCTEXT("DisplayName", "DevFramework"));
}

void FDevEdCoreModule::RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions)
{
	ICommonEdModuleInterface::RegisterAssetActions(OutAssetActions);
	OutAssetActions.Add(MakeShareable(new FGameplayProcedureActions(AssetCategory)));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevEdCoreModule, DevEdCore)
