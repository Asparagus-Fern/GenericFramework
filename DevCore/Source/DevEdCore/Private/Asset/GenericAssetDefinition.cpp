// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Asset/GenericAssetDefinition.h"

UGenericAssetDefinition::UGenericAssetDefinition(const FObjectInitializer& ObjectInitializer)
	: AssetDisplayName(NSLOCTEXT("FDevEdCoreModule", "AssetDefinition_AssetName", "New Asset")),
	  AssetDescription(NSLOCTEXT("FDevEdCoreModule", "AssetDefinition_AssetDescription", "This Is a New Asset")),
	  AssetColor(FColor(201, 29, 85)),
	  AssetClass(nullptr),
	  AssetMainCategory(NSLOCTEXT("FDevEdCoreModule", "AssetDefinition_AssetMainCategory", "Main Category")),
	  AssetSubCategory(NSLOCTEXT("FDevEdCoreModule", "AssetDefinition_AssetSubCategory", ""))
{
}

FText UGenericAssetDefinition::GetAssetDisplayName() const
{
	return AssetDisplayName;
}

FText UGenericAssetDefinition::GetAssetDescription(const FAssetData& AssetData) const
{
	return AssetDescription;
}

FLinearColor UGenericAssetDefinition::GetAssetColor() const
{
	return AssetColor;
}

TSoftClassPtr<UObject> UGenericAssetDefinition::GetAssetClass() const
{
	return AssetClass;
}

TConstArrayView<FAssetCategoryPath> UGenericAssetDefinition::GetAssetCategories() const
{
	static FAssetCategoryPath AssetCategories(NSLOCTEXT("FDevEdCoreModule", "AssetDefinition_AssetCategory", "GenericFramework"));
	const auto Categories = {AssetCategories / AssetMainCategory / AssetSubCategory};
	return Categories;
}

FAssetOpenSupport UGenericAssetDefinition::GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const
{
	return FAssetOpenSupport(OpenSupportArgs.OpenMethod, OpenSupportArgs.OpenMethod == EAssetOpenMethod::Edit, EToolkitMode::Standalone);
}

EAssetCommandResult UGenericAssetDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	return Super::OpenAssets(OpenArgs);
}
