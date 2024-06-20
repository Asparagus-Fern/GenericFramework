#include "Factory/AssetTypeActions.h"

#define LOCTEXT_NAMESPACE "FEditorActions"

FAssetTypeActions::FAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

uint32 FAssetTypeActions::GetCategories()
{
	return AssetCategory;
}

FText FAssetTypeActions::GetName() const
{
	return AssetName;
}

FColor FAssetTypeActions::GetTypeColor() const
{
	return AssetColor;
}

#undef LOCTEXT_NAMESPACE
