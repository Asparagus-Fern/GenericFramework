// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Asset/AssetDefinitionBase.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

FAssetCategoryPath UAssetDefinitionBase::DeveloperCategory(LOCTEXT("Developer_Category_Path", "Developer"));

TConstArrayView<FAssetCategoryPath> UAssetDefinitionBase::GetAssetCategories() const
{
	static const auto Categories = {DeveloperCategory};
	return Categories;
}

#undef LOCTEXT_NAMESPACE
