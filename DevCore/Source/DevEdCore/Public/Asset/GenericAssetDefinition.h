// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "GenericAssetDefinition.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericAssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()

public:
	UGenericAssetDefinition(const FObjectInitializer& ObjectInitializer);
	DEVEDCORE_API virtual FText GetAssetDisplayName() const override;
	DEVEDCORE_API virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	DEVEDCORE_API virtual FLinearColor GetAssetColor() const override;
	DEVEDCORE_API virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	DEVEDCORE_API virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	DEVEDCORE_API virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;
	DEVEDCORE_API virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;

protected:
	FText AssetDisplayName;
	FText AssetDescription;
	FLinearColor AssetColor;
	TSoftClassPtr<UObject> AssetClass;
	FText AssetMainCategory;
	FText AssetSubCategory;
};
