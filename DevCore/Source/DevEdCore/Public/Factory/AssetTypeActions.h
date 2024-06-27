#pragma once

#include "AssetTypeActions_Base.h"

class FAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

protected:
	FText AssetName;
	FColor AssetColor;
	UClass* AssetClass;
	EAssetTypeCategories::Type AssetCategory;
};
