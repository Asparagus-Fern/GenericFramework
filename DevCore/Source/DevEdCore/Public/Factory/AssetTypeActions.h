#pragma once

#include "AssetTypeActions_Base.h"

class FAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;

protected:
	EAssetTypeCategories::Type AssetCategory;
	FText AssetName;
	FColor AssetColor;
};
