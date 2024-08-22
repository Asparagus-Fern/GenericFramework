// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Engine/DataAsset.h"
#include "GameMenuSetting.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SCREENWIDGETGENERATION_API UGameMenuSetting : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* MenuTagTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "MenuTag"))
	TArray<FMenuInfo> MenuInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	FGameplayTag RootMenuTag = FGameplayTag::EmptyTag;

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void GenerateMenu();
#endif

public:
	UFUNCTION(BlueprintPure)
	bool GetMenuInfo(FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetMenuInfos(const TArray<FGameplayTag>& InMenuTags);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetChildMenuTags(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetChildMenuInfos(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetChildMenuTagsInDictionary(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetChildMenuInfosInDictionary(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetParentMenuTags(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetParentMenuInfos(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	FGameplayTag GetDirectParentMenuTag(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	bool GetDirectParentMenuInfo(FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo);

	UFUNCTION(BlueprintPure)
	FGameplayTag GetRootMenuTag() const;

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetRootMenuInfos();

protected:
	UPROPERTY()
	FGameplayTagContainer GameplayTagContainer;

public:
	UFUNCTION(BlueprintPure)
	FGameplayTagContainer GetGameplayTagContainer() const { return GameplayTagContainer; }
};
