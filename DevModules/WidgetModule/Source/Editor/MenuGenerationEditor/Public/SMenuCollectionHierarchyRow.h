// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UMenuEntityBase;
class UMenuGroupEntity;
class UMenuEntity;
class SMenuCollectionHierarchy;

/**
 * 
 */
struct FMenuCollectionHierarchyRow final : TSharedFromThis<FMenuCollectionHierarchyRow>
{
public:
	FMenuCollectionHierarchyRow(TObjectPtr<UMenuEntityBase> InMenuEntity);
	UMenuEntity* GetMenuEntity() const;
	UMenuGroupEntity* GetMenuGroupEntity() const;

private:
	TObjectPtr<UMenuEntityBase> MenuEntity = nullptr;
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
