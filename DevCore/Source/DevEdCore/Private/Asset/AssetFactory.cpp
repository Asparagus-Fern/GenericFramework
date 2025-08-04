// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Asset/AssetFactory.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

UAssetFactory::UAssetFactory()
{
	bCreateNew = true;
}

uint32 UAssetFactory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("Developer", LOCTEXT("AssetCategoryName", "Developer"));
}

#undef LOCTEXT_NAMESPACE
