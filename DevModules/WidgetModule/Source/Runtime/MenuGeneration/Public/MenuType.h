// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "MenuType.generated.h"

USTRUCT()
struct FMenuTagTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Menu"))
	FName MenuTag = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuMainName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuSubName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuToolTip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MenuIcon = nullptr;

	FMenuTagTableRow();
	FMenuTagTableRow(FName InTag);
	MENUGENERATION_API FMenuTagTableRow(FGameplayTagTableRow const& Other);
	MENUGENERATION_API FMenuTagTableRow(FMenuTagTableRow const& Other);

	MENUGENERATION_API FMenuTagTableRow& operator=(FMenuTagTableRow const& Other);
	MENUGENERATION_API bool operator==(FMenuTagTableRow const& Other) const;
	MENUGENERATION_API bool operator!=(FMenuTagTableRow const& Other) const;
	MENUGENERATION_API bool operator<(FMenuTagTableRow const& Other) const;
};
