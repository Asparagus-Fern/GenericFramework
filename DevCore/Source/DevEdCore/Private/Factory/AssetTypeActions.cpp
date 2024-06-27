#include "Factory/AssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions"

FAssetTypeActions::FAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
	AssetName = LOCTEXT("AssetName", "New Asset");
	AssetColor = FColor(201, 29, 85);
	AssetClass = UObject::StaticClass();
}


FText FAssetTypeActions::GetName() const
{
	return AssetName;
}

FColor FAssetTypeActions::GetTypeColor() const
{
	return AssetColor;
}

UClass* FAssetTypeActions::GetSupportedClass() const
{
	return AssetClass;
}

uint32 FAssetTypeActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE
