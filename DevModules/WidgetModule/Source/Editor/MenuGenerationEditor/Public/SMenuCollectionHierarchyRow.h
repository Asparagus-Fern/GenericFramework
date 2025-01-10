// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SMenuCollectionHierarchy;
class UMenuEntity;

/**
 * 
 */
struct FMenuCollectionHierarchyRow final : TSharedFromThis<FMenuCollectionHierarchyRow>
{
public:
	FMenuCollectionHierarchyRow(TObjectPtr<UMenuEntity> InMenuEntity);
	UMenuEntity* GetMenuEntity() const;

private:
	TObjectPtr<UMenuEntity> MenuEntity = nullptr;
};

typedef TSharedPtr<FMenuCollectionHierarchyRow> FMenuCollectionHierarchyRowPtr;

/**
 * 
 */
class MENUGENERATIONEDITOR_API SMenuCollectionHierarchyRow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuCollectionHierarchyRow)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FMenuCollectionHierarchyRowPtr& InRow);

private:
	FMenuCollectionHierarchyRowPtr MenuCollectionHierarchyRowPtr;
	FText GetHierarchyRowName() const;
};
