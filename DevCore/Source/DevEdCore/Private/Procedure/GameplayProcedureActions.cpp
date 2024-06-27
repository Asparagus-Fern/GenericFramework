// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedureActions.h"

#include "Procedure/GameplayProcedure.h"

#define LOCTEXT_NAMESPACE "FGameplayProcedureActions"

FGameplayProcedureActions::FGameplayProcedureActions(EAssetTypeCategories::Type InAssetCategory)
	: FAssetTypeActions(InAssetCategory)
{
	AssetName = LOCTEXT("AssetName", "Gameplay Procedure");
	AssetClass = UGameplayProcedure::StaticClass();
}

#undef LOCTEXT_NAMESPACE
