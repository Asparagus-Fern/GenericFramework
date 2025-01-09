// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuCollectionHierarchyRow.h"

#include "SlateOptMacros.h"
#include "Entity/MenuEntity.h"

FMenuCollectionHierarchyRow::FMenuCollectionHierarchyRow(TObjectPtr<UMenuEntity> InMenuEntity)
{
	MenuEntity = InMenuEntity;
}

UMenuEntity* FMenuCollectionHierarchyRow::GetMenuEntity() const
{
	return MenuEntity;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMenuCollectionHierarchyRow::Construct(const FArguments& InArgs, const FMenuCollectionHierarchyRowPtr& InRow)
{
	MenuCollectionHierarchyRowPtr = InRow;

	if (MenuCollectionHierarchyRowPtr.IsValid())
	{
		ChildSlot
		[
			SNew(STextBlock)
			.Text(FText::FromString(MenuCollectionHierarchyRowPtr->GetMenuEntity()->MenuTag.ToString()))
		];
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
