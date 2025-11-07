#include "ExternalDataEditor.h"

#include "AssetToolsModule.h"
#include "Editor.h"
#include "ExternalData.h"
#include "Engine/AssetManager.h"

#define LOCTEXT_NAMESPACE "FExternalDataEditorModule"

void FExternalDataEditorModule::StartupModule()
{
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	AssetRegistry.OnAssetsAdded().AddRaw(this, &FExternalDataEditorModule::OnAssetsAdded);
	AssetRegistry.OnAssetsRemoved().AddRaw(this, &FExternalDataEditorModule::OnAssetsRemoved);
	AssetRegistry.OnAssetRenamed().AddRaw(this, &FExternalDataEditorModule::OnAssetRenamed);
}

void FExternalDataEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
	{
		IAssetRegistry& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

		AssetRegistry.OnAssetsAdded().RemoveAll(this);
		AssetRegistry.OnAssetsRemoved().RemoveAll(this);
		AssetRegistry.OnAssetRenamed().RemoveAll(this);
	}
}

void FExternalDataEditorModule::RenameExternalData(FAssetData InAsset, const FString& OldPath)
{
	FString AssetName;
	OldPath.Split(".", nullptr, &AssetName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	if (UExternalData* ExternalData = Cast<UExternalData>(InAsset.GetAsset()))
	{
		DeleteExternalData(ExternalData);
	}
}

void FExternalDataEditorModule::DeleteExternalData(FAssetData InAsset)
{
	if (UExternalData* ExternalData = Cast<UExternalData>(InAsset.GetAsset()))
	{
		DeleteExternalData(ExternalData);
	}
}

void FExternalDataEditorModule::DeleteExternalData(UExternalData* InExternalData)
{
	const FString FilePath = InExternalData->GetJsonFilePath();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*FilePath))
	{
		PlatformFile.DeleteFile(*FilePath);
	}
}

void FExternalDataEditorModule::OnAssetsAdded(TConstArrayView<FAssetData> Assets)
{
	for (const FAssetData& AssetData : Assets)
	{
		if (AssetData.GetClass() == UExternalData::StaticClass())
		{
			Cast<UExternalData>(AssetData.GetAsset())->SaveData();
		}
	}
}

void FExternalDataEditorModule::OnAssetsRemoved(TConstArrayView<FAssetData> Assets)
{
	for (const FAssetData& AssetData : Assets)
	{
		if (AssetData.GetClass() == UExternalData::StaticClass())
		{
			DeleteExternalData(AssetData);
		}
	}
}

void FExternalDataEditorModule::OnAssetRenamed(const FAssetData& Asset, const FString& OldPath)
{
	if (Asset.GetClass() == UExternalData::StaticClass())
	{
		RenameExternalData(Asset, OldPath);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FExternalDataEditorModule, ExternalDataEditor)
