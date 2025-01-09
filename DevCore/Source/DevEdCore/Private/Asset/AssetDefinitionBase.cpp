// Fill out your copyright notice in the Description page of Project Settings.


#include "Asset/AssetDefinitionBase.h"

#define LOCTEXT_NAMESPACE "UAssetDefinition_MenuCollection"

FAssetCategoryPath UAssetDefinitionBase::DeveloperCategory(LOCTEXT("Developer_Category_Path", "Developer"));

TConstArrayView<FAssetCategoryPath> UAssetDefinitionBase::GetAssetCategories() const
{
	static const auto Categories = {DeveloperCategory};
	return Categories;
}

#undef LOCTEXT_NAMESPACE
