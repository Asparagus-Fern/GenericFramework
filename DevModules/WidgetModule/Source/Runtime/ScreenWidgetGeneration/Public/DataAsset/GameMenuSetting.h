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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "OwnerTag"))
	TArray<FMenuContainerInfo> MenuContainerInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "MenuTag"))
	TArray<FMenuInfo> MenuInfos;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer GameplayTagContainer;

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void Generate();
#endif

public:
	UFUNCTION(BlueprintPure)
	bool CheckIsValidMenuTag(FGameplayTag InMenuTag);

public:
	UFUNCTION(BlueprintPure)
	bool GetMenuInfo(FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetMenuInfos(const TArray<FGameplayTag>& InMenuTags);

	UFUNCTION(BlueprintPure)
	bool GetMenuContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure)
	TArray<FMenuContainerInfo> GetMenuContainerInfos(const TArray<FGameplayTag>& InMenuTags);

	/* Child */
public:
	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetChildMenuTags(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetChildMenuInfos(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	/* Direct Child */
public:
	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetDirectChildMenuTags(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetDirectChildMenuInfos(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	/* Parent */
public:
	UFUNCTION(BlueprintPure)
	TArray<FGameplayTag> GetParentMenuTags(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetParentMenuInfos(FGameplayTag InMenuTag, bool bIsContainOriginal = false);

	/* Direct Parent */
public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetDirectParentMenuTag(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	bool GetDirectParentMenuInfo(FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo);

	/* Root */
public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetRootMenuTag() const;

	UFUNCTION(BlueprintPure)
	TArray<FMenuInfo> GetRootMenuInfos();
};
