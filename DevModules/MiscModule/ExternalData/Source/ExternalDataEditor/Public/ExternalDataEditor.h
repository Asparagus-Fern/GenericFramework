#pragma once

#include "CoreMinimal.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class UExternalData;

class FExternalDataEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RenameExternalData(FAssetData InAsset, const FString& OldPath);
	void DeleteExternalData(FAssetData InAsset);
	void DeleteExternalData(const FString& InAssetName);

	void OnAssetsAdded(TConstArrayView<FAssetData> Assets);
	void OnAssetsRemoved(TConstArrayView<FAssetData> Assets);
	void OnAssetRenamed(const FAssetData& Asset, const FString& OldPath);
};
