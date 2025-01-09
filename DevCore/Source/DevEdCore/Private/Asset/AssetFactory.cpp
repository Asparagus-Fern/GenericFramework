// Fill out your copyright notice in the Description page of Project Settings.


#include "Asset/AssetFactory.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "UAssetFactory"

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
