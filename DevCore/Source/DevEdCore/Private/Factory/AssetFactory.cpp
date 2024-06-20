// Fill out your copyright notice in the Description page of Project Settings.


#include "Factory/AssetFactory.h"

UAssetFactory::UAssetFactory()
{
	bCreateNew = true;
	AssetName = FText::FromString("NewAsset");
}

FText UAssetFactory::GetDisplayName() const
{
	return AssetName;
}
